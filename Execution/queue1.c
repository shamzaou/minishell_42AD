#include "../minishell.h"

void	init_queue_char(t_queue_char *q)
{
	q->front = NULL;
	q->rear = NULL;
}

void	add_char_to_queue(t_queue_char *q, char c)
{
	struct s_char_queue_node	*new_node;

	new_node = (struct s_char_queue_node *)malloc(sizeof(
				struct s_char_queue_node));
	if (!new_node)
		return ;
	new_node->val = c;
	new_node->next = NULL;
	if (q->front == NULL)
	{
		q->front = new_node;
		q->rear = new_node;
	}
	else
	{
		q->rear->next = new_node;
		q->rear = new_node;
	}
}

char	pop_char_from_queue(t_queue_char *q)
{
	char						value;
	struct s_char_queue_node	*tmp;

	tmp = q->front;
	q->front = q->front->next;
	value = tmp->val;
	free(tmp);
	return (value);
}

void	add_string_to_char_queue(t_queue_char *q, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		add_char_to_queue(q, str[i]);
		i++;
	}
}

char	*char_queue_to_str(t_queue_char *q)
{
	struct s_char_queue_node	*tmp;
	char						*str;
	int							i;

	i = 0;
	tmp = q->front;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (q->front)
		str[i++] = pop_char_from_queue(q);
	str[i] = '\0';
	return (str);
}