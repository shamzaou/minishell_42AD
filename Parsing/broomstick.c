/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broomstick.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamzaou@student.42abudhabi.ae <shamzaou>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 01:58:55 by shamzaou@st       #+#    #+#             */
/*   Updated: 2024/01/08 02:04:07 by shamzaou@student ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tree(t_cmd *cmd)
{
	t_execcmd	*ecmd;
	t_pipecmd	*pcmd;
	t_redircmd	*rcmd;

	if (cmd && cmd->type == EXEC)
	{
		ecmd = (t_execcmd *)cmd;
		ft_free(ecmd);
	}
	else if (cmd && cmd->type == REDIR)
	{
		rcmd = (t_redircmd *)cmd;
		free_tree(rcmd->subcmd);
		ft_free(rcmd);
	}
	else if (cmd && cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *)cmd;
		free_tree(pcmd->left);
		free_tree(pcmd->right);
		ft_free(pcmd);
	}
}
