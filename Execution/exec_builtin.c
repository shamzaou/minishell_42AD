/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamzaou@student.42abudhabi.ae <shamzaou>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 02:22:47 by shamzaou@student  #+#    #+#             */
/*   Updated: 2024/01/09 02:23:19 by shamzaou@student ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin_command(t_execcmd *ecmd)
{
	if (ft_strcmp(ecmd->av[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(ecmd->av[0], "exit") == 0)
		return (1);
	else if (ft_strcmp(ecmd->av[0], "env") == 0)
		return (1);
	else if (ft_strcmp(ecmd->av[0], "export") == 0)
		return (1);
	else if (ft_strcmp(ecmd->av[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(ecmd->av[0], "unset") == 0)
		return (1);
	else
		return (0);
}

void	execute_builtin_commands(t_execcmd *ecmd, t_params *params,
	int exit_status)
{
	if (ft_strcmp(ecmd->av[0], "echo") == 0)
		echo(ecmd->av);
	else if (ft_strcmp(ecmd->av[0], "exit") == 0)
		exit_command(ecmd->av, params);
	else if (ft_strcmp(ecmd->av[0], "env") == 0)
		env(ecmd->av, params);
	else if (ft_strcmp(ecmd->av[0], "export") == 0)
		export(ecmd->av, params->env_var_list);
	else if (ft_strcmp(ecmd->av[0], "pwd") == 0)
		pwd(&exit_status);
	else if (ft_strcmp(ecmd->av[0], "unset") == 0)
		free_exit(params, 0);
}
