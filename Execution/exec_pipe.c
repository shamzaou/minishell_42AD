/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabdull <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 02:28:43 by alabdull          #+#    #+#             */
/*   Updated: 2024/01/09 02:57:41 by alabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	set_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

static void	handle_exit_status(t_pipe *pipe, t_params *params, int *exit_status)
{
	waitpid(pipe->pid2, &pipe->status, 0);
	if (WIFEXITED(pipe->status))
		*exit_status = WEXITSTATUS(pipe->status);
	else
		*exit_status = 1;
	write_exit_status_to_file(params, *exit_status);
	free_exit(params, *exit_status);
}

static void	execute_left_pipe(t_pipecmd *pcmd, t_params *params, t_pipe *pipe,
		int *exit_status)
{
	pipe->is_herdoc = 0;

	pipe->pid1 = forking(params);
	if (pipe->pid1 == 0)
		execute_left_subtree(pcmd->left, pipe->fd, params, exit_status);
	if (pcmd->left->type == REDIR && ((t_redircmd *)pcmd->left)->r_type == '%')
	{
		close(pipe->fd[0]);
		close(pipe->fd[1]);
		waitpid(pipe->pid1, NULL, 0);
		pipe->is_herdoc[0] = 1;
	}
}

static void	execute_right_pipe(t_pipecmd *pcmd, t_params *params, t_pipe *pipe,
		int *exit_status)
{
	pipe->is_herdoc = 0;

	pipe->pid2 = forking(params);
	if (pipe->pid2 == 0)
		execute_right_subtree(pcmd->right, pipe->fd, params, exit_status);
	set_signals();
	if (!pipe->is_herdoc)
	{
		close(pipe->fd[0]);
		close(pipe->fd[1]);
		waitpid(pipe->pid1, NULL, 0);
	}
	handle_exit_status(pipe, params, exit_status);
}

void	run_pipe(t_cmd *cmd, t_params *params, int *exit_status)
{
	int			fd[2];
	t_pipe		*pipe;
	t_pipecmd	*pcmd;

	pipe = NULL;
	pcmd = (t_pipecmd *)cmd;
	pipe1(fd, params);
	execute_left_pipe(pcmd, params, pipe, exit_status);
	execute_right_pipe(pcmd, params, pipe, exit_status);
}
