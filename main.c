/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabdull <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 05:34:40 by shamzaou          #+#    #+#             */
/*   Updated: 2024/01/08 22:09:58 by alabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_command(t_params *params, int *exit_status)
{
	int			status;
	t_execcmd	*ecmd;

	set_signal_handler(params->tree);
	if (forking(params) == 0)
	{
		save_child_pid(getpid(), params);
		run_cmd(params->tree, params, exit_status);
	}
	waitpid(-1, &status, 0);
	get_exit_status(params->tree, params, exit_status, status);
	ecmd = (t_execcmd *)params->tree;
	if (ecmd->type == EXEC && ft_strcmp(ecmd->av[0], "exit") == 0)
	{
		if (!ecmd->av[1] || (ecmd->av[1]
				&& (!is_numeric(ecmd->av[1]) || !ecmd->av[2])))
		{
			unlink("/tmp/exit_status.tmp");
			unlink("/tmp/child_pid.tmp");
			free_exit(params, *exit_status);
		}
	}
	cleanup(params);
}

static void	initialize_shell_environment(t_params *params, int *exit_status,
		char **envp)
{
	*exit_status = 0;
	params->envp = envp;
	params->env_var_list = NULL;
	init_queue(&params->args_queue);
	init_env_var_list(envp, &params->env_var_list);
}

int	is_valid_shell_input(char *buf, int *exit_status)
{
	if (ft_strlen(buf) == 0 || is_whitespace_string(buf)
		|| !validate_command(buf, exit_status))
		return (0);
	return (1);
}

static void	execute_shell_command(t_params *params, int *exit_status)
{
	add_history(params->buf);
	params->tree = parse_cmd(params->buf, exit_status);
	if (!params->tree)
	{
		ft_free(params->buf);
		return ;
	}
	handle_cmd_args(params->tree, params, exit_status);
	if (is_built_in_command(params->tree))
	{
		execute_built_in_command((t_execcmd *)params->tree,
			&params->env_var_list, exit_status);
		ft_free(params->buf);
		free_tree(params->tree);
		free_queue(&params->args_queue);
	}
	else
		execute_command(params, exit_status);
}

int	main(int ac, char **av, char **envp)
{
	t_params	params;
	int			exit_status;

	(void)ac;
	(void)av;
	initialize_shell_environment(&params, &exit_status, envp);
	while (1)
	{
		setup_signals();
		params.buf = readline(PROMPT);
		if (!params.buf)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		if (!is_valid_shell_input(params.buf, &exit_status))
		{
			ft_free(params.buf);
			continue ;
		}
		execute_shell_command(&params, &exit_status);
	}
	free_env_var_list(params.env_var_list);
	clear_history();
	return (exit_status);
}
