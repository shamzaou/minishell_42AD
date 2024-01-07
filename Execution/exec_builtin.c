#include "../minishell.h"

int	is_builtin_command(t_execcmd *ecmd)
{
	if (ft_strcmp(ecmd->argv[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(ecmd->argv[0], "exit") == 0)
		return (1);
	else if (ft_strcmp(ecmd->argv[0], "env") == 0)
		return (1);
	else if (ft_strcmp(ecmd->argv[0], "export") == 0)
		return (1);
	else if (ft_strcmp(ecmd->argv[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(ecmd->argv[0], "pwd") == 0)
		return (1);
	else
		return (0);
}

void	execute_builtin_commands(t_execcmd *ecmd, t_params *params,
	int exit_status)
{
	if (ft_strcmp(ecmd->argv[0], "echo") == 0)
		echo(ecmd->argv);
	else if (ft_strcmp(ecmd->argv[0], "exit") == 0)
		exit_command(ecmd->argv, params);
	else if (ft_strcmp(ecmd->argv[0], "env") == 0)
		env(ecmd->argv, params);
	else if (ft_strcmp(ecmd->argv[0], "export") == 0)
		export(ecmd->argv, params->env_var_list);
	else if (ft_strcmp(ecmd->argv[0], "unset") == 0)
		free_exit(params, 0);
	else if (ft_strcmp(ecmd->argv[0], "pwd") == 0)
		pwd(&exit_status);
}