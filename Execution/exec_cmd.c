/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabdull <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 02:28:35 by alabdull          #+#    #+#             */
/*   Updated: 2024/01/09 02:28:36 by alabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_cmd(t_cmd *cmd, t_params *params, int *exit_status)
{
	if (cmd->type == EXEC)
		run_exec(cmd, params, exit_status);
	else if (cmd->type == REDIR)
		run_redir(cmd, params, exit_status);
	else if (cmd->type == PIPE)
		run_pipe(cmd, params, exit_status);
	exit(*exit_status);
}
