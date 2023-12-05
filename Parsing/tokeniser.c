/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamzaou <shamzaou@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 08:12:54 by shamzaou          #+#    #+#             */
/*   Updated: 2023/12/05 10:57:55 by shamzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tokens    *tokenise(char const *line)
{
    char        **strtokens;
    t_tokens    *head;

    // token init head.prev and clear
    head = NULL;
    strtokens = ft_splitter(line, ' ');
    if (!strtokens)
        return (NULL);
    head = classify(strtokens);
    free_strtokens(strtokens);
    return (head);
}

t_tokens *create_new_token(char *value)
{
    t_tokens *new_token = (t_tokens *)malloc(sizeof(t_tokens));
    if (!new_token) {
        return NULL;
    }

    new_token->value = ft_strdup(value);
    if (!new_token->value) {
        free(new_token);
        return NULL;
    }

    new_token->type = get_type(new_token->value);
    new_token->next = NULL;
    new_token->prev = NULL;

    return new_token;
}

t_tokens *classify(char **strtokens)
{
    t_tokens    *head;
    t_tokens    *current;
    int         i;
    
    head = NULL;
    current = NULL;
    i = -1;
    while (strtokens[++i])
    {
        t_tokens *new_token = create_new_token(strtokens[i]);
        if (!new_token)
        {
            clear_tokens(head);
            return NULL;
        }
        if (!head)
            head = new_token;
        else
        {
            new_token->prev = current;
            current->next = new_token;
        }
        current = new_token;
    }
    return head;
}

void free_strtokens(char **strtokens)
{
    int i = -1;
    if (strtokens)
    {
        while (strtokens[++i])
            free(strtokens[i]);
        free(strtokens);
    }
}

t_token_type get_type(char *value)
{
    if (value == NULL)
        return INVALID;
    if (strcmp(value, "|") == 0)
        return PIPE;
    else if (strcmp(value, "<") == 0)
        return REDIRECT_IN;
    else if (strcmp(value, ">") == 0)
        return REDIRECT_OUT;
    else if (strcmp(value, ">>") == 0)
        return APPEND;
    else if (strcmp(value, "<<") == 0)
        return HEREDOC;
    else if (value[0] == '$')
        return ENV_VAR;
    else if (value[0] == '\'' && value[strlen(value) - 1] == '\'')
        return QUOTE;
    else if (value[0] == '\"' && value[strlen(value) - 1] == '\"')
        return DQUOTE;
    else
        return WORD;
}

void clear_tokens(t_tokens *head)
{
    t_tokens *current = head, *temp;
    while (current)
    {
        temp = current;
        current = current->next;
        free(temp->value);
        free(temp);
    }
}
