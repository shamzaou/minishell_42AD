/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabdull <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 02:05:31 by shamzaou@st       #+#    #+#             */
/*   Updated: 2024/01/08 03:07:07 by alabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
	{
	}
}

void	signal_handler_herdoc(int signum)
{
	int	fd;
	int	child_pid;

	if (signum == SIGINT)
	{
		printf("\n");
		fd = open("/tmp/child_pid.tmp", O_RDONLY);
		if (fd < 0)
		{
			perror("open");
			exit(1);
		}
		if (read(fd, &child_pid, sizeof(int)) < 0)
		{
			perror("read");
			exit(1);
		}
		close(fd);
		kill(child_pid, SIGKILL);
	}
	else if (signum == SIGQUIT)
		printf("\b\b  \b\b");
}

void	signal_handler_input(int signum)
{
	if (signum == SIGQUIT)
		ft_putnbr_fd1("Quit: ", signum, "\n", STDERR_FILENO);
	else if (signum == SIGINT)
		ft_putstr_fd("\n", STDERR_FILENO);
}

void	setup_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signal_handler(t_cmd *tree)
{
	if (tree && tree->type == REDIR)
	{
		signal(SIGINT, signal_handler_herdoc);
		signal(SIGQUIT, signal_handler_herdoc);
	}
	else
	{
		signal(SIGINT, signal_handler_input);
		signal(SIGQUIT, signal_handler_input);
	}
}
