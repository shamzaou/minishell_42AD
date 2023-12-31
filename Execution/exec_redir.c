/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabdull <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 02:27:55 by alabdull          #+#    #+#             */
/*   Updated: 2024/01/09 02:27:56 by alabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	process_herdoc_input_dollar(char *line, int *i, t_params *params,
	t_char_queue *q)
{
	char	*var_name;
	char	*var_value;

	(*i)++;
	var_name = getvar_name(line + *i);
	var_value = getenv_value(var_name, params->env_var_list);
	if (var_value)
		add_string_to_char_queue(q, var_value);
	*i += ft_strlen(var_name);
	ft_free(var_name);
}

static char	*precess_herdoc_input(char *line, t_params *params,
	int *exit_status)
{
	int				i;
	t_char_queue	q;
	char			*exit_status_str;

	i = 0;
	init_queue_char(&q);
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] == '?')
		{
			exit_status_str = ft_itoa(*exit_status);
			add_string_to_char_queue(&q, exit_status_str);
			free(exit_status_str);
			i += 2;
		}
		else if (line[i] == '$' && (is_whitespace(line[i + 1])))
			add_char_to_queue(&q, line[i++]);
		else if (line[i] == '$')
			process_herdoc_input_dollar(line, &i, params, &q);
		else
			add_char_to_queue(&q, line[i++]);
	}
	ft_free(line);
	return (char_queue_to_str(&q));
}

static char	*get_herdoc_input(char *delimiter, t_params *params,
	int *exit_status)
{
	t_queue	q;
	char	*line;
	int		terminal_fd;

	terminal_fd = open("/dev/tty", O_RDONLY);
	if (terminal_fd < 0)
		free_panic_exit(params, "open", 1);
	dup2(terminal_fd, STDIN_FILENO);
	close(terminal_fd);
	init_queue(&q);
	while (1)
	{
		ft_putstr_fd("> ", STDERR_FILENO);
		line = get_next_line(0);
		if (line == NULL)
			break ;
		if (ft_strlen(line) == ft_strlen(delimiter) + 1
			&& ft_strncmp(line, delimiter, ft_strlen(line) - 1) == 0)
		{
			free(line);
			break ;
		}
		add_to_queue(&q, precess_herdoc_input(line, params, exit_status));
	}
	return (queue_to_str(&q));
}

static void	write_herdoc_input(char *herdoc_input, t_params *params)
{
	int	fd;

	fd = open("/tmp/herdoc_input.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		free_panic_exit(params, "open", 1);
	if (write(fd, herdoc_input, ft_strlen(herdoc_input)) < 0)
		free_panic_exit(params, "write", 1);
	close(fd);
}

void	run_redir(t_cmd *cmd, t_params *params, int *exit_status)
{
	t_redircmd		*rcmd;
	char			*herdoc_input;

	rcmd = (t_redircmd *)cmd;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (rcmd->r_type != '-')
	{
		close(rcmd->fd);
		if (open(rcmd->file, rcmd->mode, 0644) < 0)
			free_panic_exit(params, "open", 1);
	}
	else
	{
		herdoc_input = get_herdoc_input(rcmd->file, params, exit_status);
		write_herdoc_input(herdoc_input, params);
		free(herdoc_input);
		close(rcmd->fd);
		if (open("/tmp/herdoc_input.tmp", rcmd->mode, 0644) < 0)
			free_panic_exit(params, "open", 1);
	}
	run_cmd(rcmd->subcmd, params, exit_status);
}
