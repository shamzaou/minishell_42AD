/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer_helpers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabdull <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 02:05:01 by shamzaou@st       #+#    #+#             */
/*   Updated: 2024/01/08 02:53:41 by alabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_invalid_pipe_syntax(char **ps, char *es, int *exit_status)
{
	if (peek(ps, es, "|"))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", STDERR_FILENO);
		*exit_status = 258;
		return (1);
	}
	return (0);
}

int	validate_redirection(char **ps, char *es, int *exit_status)
{
	char	*q;
	char	*eq;
	int		tok;

	tok = get_next_token(ps, es, &q, &eq);
	if (tok == '\0')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", STDERR_FILENO);
		*exit_status = 258;
		return (0);
	}
	else if (tok != 'a')
	{
		*eq = '\0';
		ft_putstr_fd1("minishell: syntax error near unexpected token `", q ,"'\n", STDERR_FILENO);
		*exit_status = 258;
		return (0);
	}
	return (1);
}

int	validate_pipe(char **ps, char *es, int *exit_status)
{
	int	tok;

	tok = get_next_token(ps, es, 0, 0);
	if (tok == '|' || tok == '\0')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", STDERR_FILENO);
		*exit_status = 258;
		return (0);
	}
	return (1);
}