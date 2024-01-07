/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamzaou@student.42abudhabi.ae <shamzaou>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 01:03:30 by shamzaou          #+#    #+#             */
/*   Updated: 2024/01/08 02:04:42 by shamzaou@student ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	parse_exec_arg(t_execcmd **ecmd, char **ps, char *es, int *argc)
{
	int		tok;
	char	*q;
	char	*eq;

	tok = get_next_token(ps, es, &q, &eq);
	if (tok == '\0')
		return (0);
	(*ecmd)->argv[*argc] = q;
	(*ecmd)->eargv[*argc] = eq;
	(*argc)++;
	return (1);
}

static void	parse_next_redir(t_cmd **cmd, t_execcmd **ecmd, char **ps, char *es)
{
	t_cmd	*tmp;

	if ((*cmd) != (t_cmd *)(*ecmd))
	{
		tmp = (*cmd);
		while (((t_redircmd *)tmp)->subcmd->type == REDIR)
			tmp = ((t_redircmd *)tmp)->subcmd;
		((t_redircmd *)tmp)->subcmd = parse_redir((t_cmd *)(*ecmd), ps, es);
	}
	else
		(*cmd) = parse_redir((*cmd), ps, es);
}

t_cmd	*parse_exec(char **ps, char *es, int *error)
{
	t_execcmd	*ecmd;
	t_cmd		*cmd;
	int			argc;

	argc = 0;
	cmd = execcmd();
	ecmd = (t_execcmd *)cmd;
	cmd = parse_redir(cmd, ps, es);
	while (!peek(ps, es, "|"))
	{
		if (!parse_exec_arg(&ecmd, ps, es, &argc))
			break ;
		if (argc >= MAXARGS)
		{
			*error = 1;
			free_tree(cmd);
			return (NULL);
		}
		parse_next_redir(&cmd, &ecmd, ps, es);
	}
	ecmd->argv[argc] = NULL;
	ecmd->eargv[argc] = NULL;
	return (cmd);
}
