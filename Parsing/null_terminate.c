/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null_terminate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamzaou@student.42abudhabi.ae <shamzaou>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:05:35 by shamzaou          #+#    #+#             */
/*   Updated: 2024/01/08 02:04:32 by shamzaou@student ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	null_terminate_pipe(t_cmd *cmd)
{
	t_pipecmd	*pcmd;

	pcmd = (t_pipecmd *)cmd;
	null_terminate_command(pcmd->right);
	null_terminate_command(pcmd->left);
}

static void	null_terminate_redir(t_cmd *cmd)
{
	t_redircmd	*rcmd;

	rcmd = (t_redircmd *)cmd;
	*rcmd->efile = '\0';
	null_terminate_command(rcmd->subcmd);
}

static t_cmd	*null_terminate_exec(t_cmd *cmd)
{
	int			i;
	t_execcmd	*ecmd;

	i = 0;
	ecmd = (t_execcmd *)cmd;
	while (ecmd->av[i])
	{
		*ecmd->eargv[i] = '\0';
		i++;
	}
	return (cmd);
}

t_cmd	*null_terminate_command(t_cmd *cmd)
{
	if (cmd->type == PIPE)
		null_terminate_pipe(cmd);
	else if (cmd->type == REDIR)
		null_terminate_redir(cmd);
	else if (cmd->type == EXEC)
		null_terminate_exec(cmd);
	return (cmd);
}
