#include "../minishell.h"

static void	execute_external_command(t_cmd *cmd, t_params *params)
{
	t_execcmd	*ecmd;
	char		*path_var;
	char		*binary_path;

	binary_path = NULL;
	ecmd = (t_execcmd *)cmd;
	path_var = getenv_value("PATH", params->env_var_list);
	if (path_var == NULL)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: %s: No such file or directory\n",
			ecmd->argv[0]);
		free_exit(params, 127);
	}
	binary_path = find_command_path(ecmd->argv[0], path_var);
	if (binary_path == NULL)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: %s: command not found\n",
			ecmd->argv[0]);
		free_exit(params, 127);
	}
	execve(binary_path, ecmd->argv, params->envp);
	ft_free(binary_path);
	free_exit(params, 126);
}

void	run_exec(t_cmd *cmd, t_params *params, int *exit_status)
{
	t_execcmd	*ecmd;

	ecmd = (t_execcmd *)cmd;
	remove_empty_args(ecmd);
	handle_executable_path(ecmd, params);
	if (is_builtin_command(ecmd))
	{
		execute_builtin_commands(ecmd, params, *exit_status);
		free_exit(params, 0);
	}
	else
	{
		if (access(ecmd->argv[0], X_OK) == 0)
		{
			execve(ecmd->argv[0], ecmd->argv, params->envp);
			ft_printf_fd(STDERR_FILENO, "minishell: %s: command not found\n",
				ecmd->argv[0]);
			free_exit(params, 127);
		}
		else
			execute_external_command(cmd, params);
	}
}
