/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabdull <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 02:28:07 by alabdull          #+#    #+#             */
/*   Updated: 2024/01/09 02:28:08 by alabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
}

void	free_split(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

void	free_exit(t_params *params, int exit_status)
{
	ft_free(params->buf);
	free_tree(params->tree);
	free_env_var_list(params->env_var_list);
	free_queue(&params->args_queue);
	exit(exit_status);
}

void	free_panic_exit(t_params *params, char *error, int exit_status)
{
	ft_free(params->buf);
	free_tree(params->tree);
	free_env_var_list(params->env_var_list);
	free_queue(&params->args_queue);
	perror(error);
	exit(exit_status);
}
