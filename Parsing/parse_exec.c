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

static int	parse_exec_args(t_execcmd **ecmd, char **ps, char *es, int *ac)
{
	int		tok;
	char	*q;
	char	*eq;

	tok = get_next_token(ps, es, &q, &eq);
	if (tok == '\0')
		return (0);
	(*ecmd)->av[*ac] = q;
	(*ecmd)->eargv[*ac] = eq;
	(*ac)++;
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
	t_cmd		*cmd;
	t_execcmd	*ecmd;
	int			ac;

	ac = 0;
	cmd = execcmd();
	ecmd = (t_execcmd *)cmd;
	cmd = parse_redir(cmd, ps, es);
	while (!peek(ps, es, "|"))
	{
		if (!parse_exec_args(&ecmd, ps, es, &ac))
			break ;
		if (ac >= MAXARGS)
		{
			*error = 1;
			free_tree(cmd);
			return (NULL);
		}
		parse_next_redir(&cmd, &ecmd, ps, es);
	}
	ecmd->av[ac] = NULL;
	ecmd->eargv[ac] = NULL;
	return (cmd);
}
