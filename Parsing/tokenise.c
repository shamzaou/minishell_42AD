/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamzaou@student.42abudhabi.ae <shamzaou>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 08:12:54 by shamzaou          #+#    #+#             */
/*   Updated: 2024/01/08 02:05:15 by shamzaou@student ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_operators(char **s, int *token)
{
	if (*token == '\0')
		*token = '\0';
	else if (*token == '|')
		(*s)++;
	else if (*token == '>')
	{
		(*s)++;
		if (**s == '>')
		{
			*token = '+';
			(*s)++;
		}
	}
	else if (*token == '<')
	{
		(*s)++;
		if (**s == '<')
		{
			*token = '%';
			(*s)++;
		}
	}
	else
		*token = 'a';
}

static void	skip_non_special_tokens(char **s, char *es)
{
	while (*s < es && !is_whitespace(**s) && !ft_strchr("<|>", **s))
	{
		if (**s == '\"')
		{
			(*s)++;
			while (*s < es && **s != '\"')
				(*s)++;
		}
		else if (**s == '\'')
		{
			(*s)++;
			while (*s < es && **s != '\'')
				(*s)++;
		}
		if (*s < es)
			(*s)++;
	}
}

int	get_next_token(char **ps, char *es, char **q, char **eq)
{
	int		token;
	char	*s;

	s = *ps;
	while (s < es && is_whitespace(*s))
		s++;
	if (q)
		*q = s;
	token = *s;
	handle_operators(&s, &token);
	if (token == 'a')
		skip_non_special_tokens(&s, es);
	if (eq)
		*eq = s;
	while (s < es && is_whitespace(*s))
		s++;
	*ps = s;
	return (token);
}

int	peek(char **ps, char *es, char *tokens)
{
	char	*s;

	s = *ps;
	while (s < es && is_whitespace(*s))
		s++;
	*ps = s;
	return (*s && ft_strchr(tokens, *s));
}
