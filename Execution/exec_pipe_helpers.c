/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabdull <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 02:28:38 by alabdull          #+#    #+#             */
/*   Updated: 2024/01/09 03:09:53 by alabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_and_wait(t_pipe pipe)
{
	close(pipe.fd[0]);
	close(pipe.fd[1]);
	waitpid(pipe.pid1, NULL, 0);
}

static void	write_and_exit(t_params *params, int *exit_status)
{
	write_exit_status_to_file(params, *exit_status);
	free_exit(params, *exit_status);
}

void	extra(t_pipe pipe, t_params *params, int *exit_status)
{
	set_signals();
	close_and_wait(pipe);
	waitpid(pipe.pid2, &pipe.status, 0);
	if (WIFEXITED(pipe.status))
		*exit_status = WEXITSTATUS(pipe.status);
	else
		*exit_status = 1;
	write_and_exit(params, exit_status);
}
