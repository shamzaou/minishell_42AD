/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamzaou <shamzaou@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 05:34:40 by shamzaou          #+#    #+#             */
/*   Updated: 2023/12/05 11:22:06 by shamzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
        TESTING TOKENISATION
        
const char *token_type_to_string(t_token_type type) {
    switch (type) {
        case WORD: return "WORD";
        case PIPE: return "PIPE";
        case REDIRECT_IN: return "REDIRECT_IN";
        case REDIRECT_OUT: return "REDIRECT_OUT";
        case APPEND: return "APPEND";
        case HEREDOC: return "HEREDOC";
        case ENV_VAR: return "ENV_VAR";
        case QUOTE: return "QUOTE";
        case DQUOTE: return "DQUOTE";
        default: return "UNKNOWN";
    }
}

// Function to print the contents of the token list
void print_token_list(t_tokens *tokens) {
    t_tokens *current = tokens;
    while (current != NULL) {
        printf("Token: %-15s Type: %s\n", current->value, token_type_to_string(current->type));
        current = current->next;
    }
}
*/

int main(int argc, char **argv, char **env)
{
    char        *line;
    t_tokens    *tokens;
    
    (void)argv;
    (void)env;
    if (argc != 1)
        return (1);
    //init_shell(env);
    while (1)
    {
        line = readline(PROMPT);
        if (line != NULL)
        {
            if (line && *line)
                add_history(line);
            tokens = tokenise(line);
            //print_token_list(tokens);
            free(line);
            //if (!syntax_error(tokens))
            //    execution(&tokens);
            //else
                clear_tokens(tokens);
        }
        else
            continue;
    }
    return (0);
}