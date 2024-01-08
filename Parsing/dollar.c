/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamzaou@student.42abudhabi.ae <shamzaou>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 02:03:58 by shamzaou@student  #+#    #+#             */
/*   Updated: 2024/01/08 02:04:04 by shamzaou@student ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_env_dollar(int *values[2], t_queue_char *q, char *arg,
		t_params *params)
{
	char	*var_name;
	char	*var_value;
	int		*i;

	i = values[0];
	var_name = getvar_name(arg + *i);
	var_value = getenv_value(var_name, params->env_var_list);
	if (var_value)
		enqueue_str(q, var_value);
	(*i) += ft_strlen(var_name);
	ft_free(var_name);
}

void	handle_dollar(int *values[2], t_queue_char *q, char *arg,
		t_params *params)
{
	char	*exit_status_str;
	int		*i;
	int		*exit_status;

	i = values[0];
	exit_status = values[1];
	(*i)++;
	if (!arg[*i] || is_whitespace(arg[*i]))
	{
		enqueue_char(q, '$');
		return ;
	}
	else if (arg[*i] == '?')
	{
		exit_status_str = ft_itoa(*exit_status);
		enqueue_str(q, exit_status_str);
		free(exit_status_str);
		(*i)++;
	}
	else
		handle_env_dollar(values, q, arg, params);
}
