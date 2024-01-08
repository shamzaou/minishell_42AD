/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabdull <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 02:28:43 by alabdull          #+#    #+#             */
/*   Updated: 2024/01/09 03:11:30 by alabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	execute_left_subtree(t_cmd *cmd, int fd[2], t_params *params,
		int *exit_status)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	run_cmd(cmd, params, exit_status);
	exit(0);
}

static void	execute_right_subtree(t_cmd *cmd, int fd[2], t_params *params,
		int *exit_status)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	run_cmd(cmd, params, exit_status);
	exit(0);
}

void	write_exit_status_to_file(t_params *params, int exit_status)
{
	int	fd;

	fd = open("/tmp/exit_status.tmp", O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd < 0)
		free_panic_exit(params, "open", 1);
	if (write(fd, &exit_status, sizeof(int)) < 0)
		free_panic_exit(params, "write", 1);
	close(fd);
}

void	set_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	run_pipe(t_cmd *cmd, t_params *params, int *exit_status)
{
	int			is_herdoc;
	t_pipe		pipe;
	t_pipecmd	*pcmd;

	is_herdoc = 0;
	pcmd = (t_pipecmd *)cmd;
	pipe1(pipe.fd, params);
	pipe.pid1 = forking(params);
	if (pipe.pid1 == 0)
		execute_left_subtree(pcmd->left, pipe.fd, params, exit_status);
	if (pcmd->left->type == REDIR && ((t_redircmd *)pcmd->left)->r_type == '-')
	{
		close_and_wait(pipe);
		is_herdoc = 1;
	}
	pipe.pid2 = forking(params);
	if (pipe.pid2 == 0)
		execute_right_subtree(pcmd->right, pipe.fd, params, exit_status);
	set_signals();
	if (!is_herdoc)
		close_and_wait(pipe);
	waitpid(pipe.pid2, &pipe.status, 0);
	extra(pipe, params, exit_status);
}
