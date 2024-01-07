#include "../../minishell.h"

char	*extract_variable_name(char *arg, char *equal_sign)
{
	char	*key;

	if (!equal_sign)
		return (ft_strdup(arg));
	key = ft_substr(arg, 0, equal_sign - arg);
	return (key);
}

int	is_valid_variable_name(char *key)
{
	int	i;

	i = 0;
	if (!ft_isalpha(key[i]) && key[i] != '_')
		return (0);
	i++;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
