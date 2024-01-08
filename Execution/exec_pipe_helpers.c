#include "../minishell.h"

void	execute_left_subtree(t_cmd *cmd, int fd[2], t_params *params,
	int *exit_status)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	run_cmd(cmd, params, exit_status);
	exit(0);
}

void	execute_right_subtree(t_cmd *cmd, int fd[2], t_params *params,
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

