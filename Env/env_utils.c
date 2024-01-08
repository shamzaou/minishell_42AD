/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabdull <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 22:03:43 by alabdull          #+#    #+#             */
/*   Updated: 2024/01/08 22:03:45 by alabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env_var_node(t_env_var *node)
{
	if (node->key)
		ft_free(node->key);
	if (node->value)
		ft_free(node->value);
	ft_free(node);
}

void	free_env_var_list(t_env_var *env_var_list)
{
	t_env_var	*tmp;
	t_env_var	*current;

	current = env_var_list;
	while (current)
	{
		tmp = current->next;
		free_env_var_node(current);
		current = tmp;
	}
}

char	*getenv_value(char *key, t_env_var *env_var_list)
{
	t_env_var	*tmp;

	tmp = env_var_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
