#include "../minishell.h"

void	process_single_quote(char *arg, int *i, t_queue_char *q)
{
	(*i)++;
	while (arg[*i] && arg[*i] != '\'')
	{
		enqueue_char(q, arg[*i]);
		(*i)++;
	}
	(*i)++;
}

void	process_double_quote_2(int *values[2], char *arg, t_queue_char *q,
		t_params *params)
{
	char	*var_name;
	char	*var_value;
	int		*i;

	i = values[0];
	(*i)++;
	var_name = getvar_name(arg + *i);
	var_value = getenv_value(var_name, params->env_var_list);
	if (var_value)
		enqueue_str(q, var_value);
	(*i) += ft_strlen(var_name);
	ft_free(var_name);
}

void	process_double_quote_3(int *values[2], t_queue_char *q)
{
	char	*exit_status_str;
	int		*i;
	int		*exit_status;

	i = values[0];
	exit_status = values[1];
	exit_status_str = ft_itoa(*exit_status);
	enqueue_str(q, exit_status_str);
	free(exit_status_str);
	(*i) += 2;
}

void	process_double_quote(int *values[2], char *arg, t_queue_char *q,
		t_params *params)
{
	int	*i;

	i = values[0];
	(*i)++;
	while (arg[*i] && arg[*i] != '\"')
	{
		if (arg[*i] == '$' && (is_whitespace(arg[*i + 1])
				|| arg[*i + 1] == '\"'))
		{
			enqueue_char(q, '$');
			(*i)++;
		}
		else if (arg[*i] == '$' && arg[*i + 1] == '?')
			process_double_quote_3(values, q);
		else if (arg[*i] == '$')
			process_double_quote_2(values, arg, q, params);
		else
			enqueue_char(q, arg[(*i)++]);
	}
	(*i)++;
}