/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamzaou <shamzaou@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:05:35 by shamzaou          #+#    #+#             */
/*   Updated: 2023/12/05 12:18:33 by shamzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	null_terminate_pipe(t_cmd *cmd)
{
	t_pipecmd	*pcmd;

	pcmd = (t_pipecmd *)cmd;
	null_terminate_command(pcmd->left);
	null_terminate_command(pcmd->right);
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
	while (ecmd->argv[i])
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
