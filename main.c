/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamzaou <shamzaou@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 05:34:40 by shamzaou          #+#    #+#             */
/*   Updated: 2023/12/05 06:29:27 by shamzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
    char        *line;
    t_tokens    *tokens;
    
    if (argc != 1)
        return (1);
    init_shell();
    while (1)
    {
        line = readline(PROMPT);
        if (line != NULL)
        {
            add_history(line);
            tokens = tokenise(line);
            free(line);
            if (!syntax_error(tokens)
                minishell(&tokens);
            else
                clear_tokens(&tokens);
        }
        else
            ctrld();
    }
    return (0);
}