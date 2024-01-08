#include "../minishell.h"

static void	set_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

static void	handle_exit_status(int pid2, t_params *params, int *exit_status)
{
	int	status;

	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		*exit_status = WEXITSTATUS(status);
	else
		*exit_status = 1;
	write_exit_status_to_file(params, *exit_status);
	free_exit(params, *exit_status);
}

static void	execute_left_pipe(t_pipecmd *pcmd, int *fd, t_params *params,
		int *exit_status, int *pid1, int *is_herdoc)
{
	*pid1 = forking(params);
	if (*pid1 == 0)
		execute_left_subtree(pcmd->left, fd, params, exit_status);
	if (pcmd->left->type == REDIR && ((t_redircmd *)pcmd->left)->r_type == '%')
	{
		close(fd[0]);
		close(fd[1]);
		waitpid(*pid1, NULL, 0);
		*is_herdoc = 1;
	}
}

static void	execute_right_pipe(t_pipecmd *pcmd, int *fd, t_params *params,
		int *exit_status, int *pid1, int *is_herdoc)
{
	int	pid2;

	pid2 = forking(params);
	if (pid2 == 0)
		execute_right_subtree(pcmd->right, fd, params, exit_status);
	set_signals();
	if (!*is_herdoc)
	{
		close(fd[0]);
		close(fd[1]);
		waitpid(*pid1, NULL, 0);
	}
	handle_exit_status(pid2, params, exit_status);
}

void	run_pipe(t_cmd *cmd, t_params *params, int *exit_status)
{
	int fd[2];
	int pid1;
	int is_herdoc = 0;
	t_pipecmd *pcmd;

	pcmd = (t_pipecmd *)cmd;
	pipe1(fd, params);
	execute_left_pipe(pcmd, fd, params, exit_status, &pid1, &is_herdoc);
	execute_right_pipe(pcmd, fd, params, exit_status, &pid1, &is_herdoc);
}