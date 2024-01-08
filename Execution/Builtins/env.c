/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabdull <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 02:29:23 by alabdull          #+#    #+#             */
/*   Updated: 2024/01/09 02:29:24 by alabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	env(char **av, t_params *params)
{
	t_env_var	*tmp;

	if (av[1])
	{
		ft_putstr_fd1("env: ", av[1], ": No such file or directory\n", 2);
		free_exit(params, 127);
	}
	tmp = params->env_var_list;
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}
