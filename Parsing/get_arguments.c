/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arguments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamzaou@student.42abudhabi.ae <shamzaou>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 08:21:40 by shamzaou          #+#    #+#             */
/*   Updated: 2024/01/08 02:04:23 by shamzaou@student ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	process_args(char *arg, t_queue_char *q, int *exit_status,
		t_params *params)
{
	int	i;
	int	*values[2];

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\'')
			get_quote(arg, &i, q);
		else if (arg[i] == '\"')
		{
			values[0] = &i;
			values[1] = exit_status;
			handle_dquotes(values, arg, q, params);
		}
		else if (arg[i] == '$')
		{
			values[0] = &i;
			values[1] = exit_status;
			handle_dollar(values, q, arg, params);
		}
		else
			add_char_to_queue(q, arg[i++]);
	}
}

static char	*get_args(char *arg, t_params *params, int *exit_status)
{
	t_queue_char	q;
	char			*clean_arg;

	init_queue_char(&q);
	if (ft_strcmp(arg, "~") == 0)
	{
		clean_arg = ft_strdup(getenv_value("HOME", params->env_var_list));
		add_to_queue(&params->args_queue, clean_arg);
		return (clean_arg);
	}
	process_args(arg, &q, exit_status, params);
	clean_arg = char_queue_to_str(&q);
	add_to_queue(&params->args_queue, clean_arg);
	return (clean_arg);
}

static void	handle_exec_cmd_args(t_cmd *cmd, t_params *params, int *exit_status)
{
	int			i;
	t_execcmd	*ecmd;

	i = 0;
	ecmd = (t_execcmd *)cmd;
	while (ecmd->av[i])
	{
		if (contains_special_char(ecmd->av[i]))
			ecmd->av[i] = get_args(ecmd->av[i], params, exit_status);
		i++;
	}
}

void	handle_cmd_args(t_cmd *cmd, t_params *params, int *exit_status)
{
	t_pipecmd	*pcmd;
	t_redircmd	*rcmd;

	if (cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *)cmd;
		handle_cmd_args(pcmd->left, params, exit_status);
		handle_cmd_args(pcmd->right, params, exit_status);
	}
	else if (cmd->type == REDIR)
	{
		rcmd = (t_redircmd *)cmd;
		if (rcmd->r_type != '%' && contains_special_char(rcmd->file))
			rcmd->file = get_args(rcmd->file, params, exit_status);
		handle_cmd_args(rcmd->subcmd, params, exit_status);
	}
	else if (cmd->type == EXEC)
		handle_exec_cmd_args(cmd, params, exit_status);
}
