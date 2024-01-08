#include "../../minishell.h"

static int	is_newline_flag(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '-')
	{
		while (str[i] && str[i] == 'n')
			i++;
		if (str[i] == '\0')
			return (1);
	}
	return (0);
}

void	echo(char **av)
{
	int		i;
	int		new_line;

	i = 1;
	new_line = 1;
	while (av[i] && is_newline_flag(av[i]))
	{
		new_line = 0;
		i++;
	}
	while (av[i])
	{
		printf("%s", av[i]);
		if (av[i++ + 1])
			printf(" ");
	}
	if (new_line)
		printf("\n");
}
