#include "../../minishell.h"

static void	remove_env_var(t_env_var **env_var_list, char *arg)
{
	t_env_var	*p;
	t_env_var	*q;

	p = *env_var_list;
	q = NULL;
	while (p && ft_strcmp(p->key, arg) != 0)
	{
		q = p;
		p = p->next;
	}
	if (p == NULL)
		return ;
	q->next = p->next;
	free_env_var_node(p);
}

void	unset_env_var(char **args, t_env_var **env_var_list, int *exit_status)
{
	int			i;
	t_env_var	*p;

	i = 1;
	while (args[i])
	{
		if (!is_valid_variable_name(args[i]))
		{
			ft_putstr_fd1("minishell: unset: `", args[i],
				"': not a valid identifier\n", 2);
			*exit_status = 1;
			i++;
			continue ;
		}
		p = *env_var_list;
		if (ft_strcmp((*env_var_list)->key, args[i]) == 0)
		{
			*env_var_list = (*env_var_list)->next;
			free_env_var_node(p);
			return ;
		}
		remove_env_var(env_var_list, args[i]);
		i++;
	}
}
