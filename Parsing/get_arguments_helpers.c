#include "../minishell.h"

int	contains_special_char(char *arg)
{
	if (ft_strchr(arg, '\'') || ft_strchr(arg, '\"') || ft_strchr(arg, '$')
		|| ft_strchr(arg, '~'))
		return (1);
	return (0);
}

char	*getvar_name(char *arg)
{
	int	i;
	int	n;

	i = 0;
	if (ft_isdigit(arg[i]))
	{
		n = arg[i] - '0';
		return (ft_itoa(n));
	}
	while (arg[i] && ((ft_isalnum(arg[i]) || arg[i] == '_')))
		i++;
	return (ft_substr(arg, 0, i));
}