/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabdull <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 02:29:26 by alabdull          #+#    #+#             */
/*   Updated: 2024/01/09 02:29:27 by alabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	handle_non_numeric_arg(char *arg, t_params *params)
{
	printf("exit\n");
	ft_putstr_fd1("minishell: exit: ", arg, ": numeric argument required\n",
		STDERR_FILENO);
	free_exit(params, 255);
}

static void	handle_too_many_args(t_params *params)
{
	printf("exit\n");
	ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
	free_exit(params, 1);
}

void	exit_command(char **av, t_params *params)
{
	long long	exit_code;
	int			over_under_flow;

	if (av[1])
	{
		if (!is_numeric(av[1]))
			handle_non_numeric_arg(av[1], params);
		else if (av[2])
			handle_too_many_args(params);
		else
		{
			printf("exit\n");
			exit_code = ft_atoll(av[1], &over_under_flow);
			if (over_under_flow)
			{
				ft_putstr_fd1("minishell: exit: ", av[1],
					": numeric argument required\n", STDERR_FILENO);
				free_exit(params, 255);
			}
			free_exit(params, exit_code);
		}
	}
}
