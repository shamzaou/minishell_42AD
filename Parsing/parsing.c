/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabdull <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 02:04:44 by shamzaou@st       #+#    #+#             */
/*   Updated: 2024/01/08 02:45:23 by alabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*parse_cmd(char *buf, int *exit_status)
{
	t_cmd	*cmd;
	char	*ps;
	char	*es;
	int		error;

	ps = buf;
	es = ps + ft_strlen(buf);
	error = 0;
	cmd = parse_pipe(&ps, es, &error);
	peek(&ps, es, "");
	if (ps != es || error == 1)
	{
		if (error == 1)
			ft_putstr_fd("minishell: too many arguments\n", STDERR_FILENO);
		else
			ft_putstr_fd("minishell: syntax error\n", STDERR_FILENO);
		*exit_status = 100;
		free_tree(cmd);
		return (NULL);
	}
	null_terminate_command(cmd);
	return (cmd);
}

t_cmd	*parse_pipe(char **ps, char *es, int *error)
{
	t_cmd	*cmd;

	cmd = parse_exec(ps, es, error);
	if (peek(ps, es, "|"))
	{
		get_next_token(ps, es, 0, 0);
		cmd = pipecmd(cmd, parse_pipe(ps, es, error));
	}
	return (cmd);
}

t_cmd	*parse_redir(t_cmd *subcmd, char **ps, char *es)
{
	char	*q;
	char	*eq;
	int		tok;
	t_cmd	*cmd;

	cmd = subcmd;
	if (peek(ps, es, "<>"))
	{
		tok = get_next_token(ps, es, 0, 0);
		get_next_token(ps, es, &q, &eq);
		if (tok == '<')
			cmd = redircmd(parse_redir(subcmd, ps, es),
					redirdata(q, eq, O_RDONLY, 0), '<');
		else if (tok == '>')
			cmd = redircmd(parse_redir(subcmd, ps, es),
					redirdata(q, eq, O_WRONLY | O_CREAT | O_TRUNC, 1), '>');
		else if (tok == '%')
			cmd = redircmd(parse_redir(subcmd, ps, es),
					redirdata(q, eq, O_RDONLY, 0), '%');
		else if (tok == '+')
			cmd = redircmd(parse_redir(subcmd, ps, es),
					redirdata(q, eq, O_WRONLY | O_CREAT | O_APPEND, 1), '+');
	}
	return (cmd);
}
