/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamzaou@student.42abudhabi.ae <shamzaou>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 02:04:52 by shamzaou@student  #+#    #+#             */
/*   Updated: 2024/01/08 02:04:57 by shamzaou@student ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_quote(char *arg, int *i, t_char_queue *q)
{
	(*i)++;
	while (arg[*i] && arg[*i] != '\'')
	{
		add_char_to_queue(q, arg[*i]);
		(*i)++;
	}
	(*i)++;
}

void	handle_dquotes_envar(int *values[2], char *arg, t_char_queue *q,
		t_params *params)
{
	char	*var_name;
	char	*var_value;
	int		*i;

	i = values[0];
	(*i)++;
	var_name = getvar_name(arg + *i);
	var_value = getenv_value(var_name, params->env_var_list);
	if (var_value)
		add_string_to_char_queue(q, var_value);
	(*i) += ft_strlen(var_name);
	ft_free(var_name);
}

void	handle_dquotes_exitstatus(int *values[2], t_char_queue *q)
{
	char	*exit_status_str;
	int		*i;
	int		*exit_status;

	i = values[0];
	exit_status = values[1];
	exit_status_str = ft_itoa(*exit_status);
	add_string_to_char_queue(q, exit_status_str);
	free(exit_status_str);
	(*i) += 2;
}

void	handle_dquotes(int *values[2], char *arg, t_char_queue *q,
		t_params *params)
{
	int	*i;

	i = values[0];
	(*i)++;
	while (arg[*i] && arg[*i] != '\"')
	{
		if (arg[*i] == '$' && (is_whitespace(arg[*i + 1])
				|| arg[*i + 1] == '\"'))
		{
			add_char_to_queue(q, '$');
			(*i)++;
		}
		else if (arg[*i] == '$' && arg[*i + 1] == '?')
			handle_dquotes_exitstatus(values, q);
		else if (arg[*i] == '$')
			handle_dquotes_envar(values, arg, q, params);
		else
			add_char_to_queue(q, arg[(*i)++]);
	}
	(*i)++;
}