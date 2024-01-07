/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Recursive_Descent_Parser.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamzaou <shamzaou@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 01:03:30 by shamzaou          #+#    #+#             */
/*   Updated: 2023/12/18 01:08:05 by shamzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>



t_command *parse_command(t_tokens **current_token) {
    t_command *cmd = malloc(sizeof(t_command));
    if (!cmd) return NULL;

    cmd->name = parse_command_name(current_token);
    if (!cmd->name) {
        free(cmd);
        return NULL;
    }

    cmd->args = parse_arguments(current_token);
    // cmd->args can be NULL if there are no arguments, which is fine
    return cmd;
}

char *parse_command_name(t_tokens **current_token) {
    if (*current_token && (*current_token)->type == WORD) {
        char *name = strdup((*current_token)->value);
        *current_token = (*current_token)->next;
        return name;
    }
    return NULL;
}

char **parse_arguments(t_tokens **current_token) {
    int arg_count = 0;
    t_tokens *tmp = *current_token;
    
    // Count arguments
    while (tmp && tmp->type == WORD) {
        arg_count++;
        tmp = tmp->next;
    }

    if (arg_count == 0) return NULL;

    char **args = malloc(sizeof(char *) * (arg_count + 1));  // +1 for NULL termination
    if (!args) return NULL;

    for (int i = 0; i < arg_count; i++) {
        args[i] = strdup((*current_token)->value);
        *current_token = (*current_token)->next;
    }
    args[arg_count] = NULL;  // NULL-terminate the array

    return args;
}
