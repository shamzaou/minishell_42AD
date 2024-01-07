#include "parsing.h"

t_command_node *command_split(char const *line)
{
    char            **commands;
    t_command_node  *head;
    t_command_node  *current;
    int             i;

    commands = ft_splitter(line, "|<>");
    if (!commands)
        return NULL;
    
    head = create_new_command_node(commands[0]);
    current = head;
    i = 1;
    while (commands[i])
    {
        current->next = create_new_command_node(commands[i]);
        if (!current->next)
        {
            free_command_list(head);
            return NULL;
        }
        current = current->next;
        i++;
    }
    free_strtokens(commands);
    return head;
}

t_command_node *create_new_command_node(char *value)
{
    t_command_node *new_command_node = (t_command_node *)malloc(sizeof(t_command_node));
    if (!new_command_node)
        return NULL;
    
    new_command_node->command = parse_command(value);
    if (!new_command_node->command)
    {
        free(new_command_node);
        return NULL;
    }

    new_command_node->next = NULL;
    return new_command_node;
}

t_command *parse_command(char *value)
{
    t_command *new_command = (t_command *)malloc(sizeof(t_command));
    if (!new_command)
        return NULL;
    
    new_command->name = ft_splitter(value, " ");
    if (!new_command->name)
    {
        free(new_command);
        return NULL;
    }

    new_command->args = ft_splitter(value, " ");
    if (!new_command->args)
    {
        free(new_command->name);
        free(new_command);
        return NULL;
    }

    return new_command;
}

void free_command_list(t_command_node *head)
{
    t_command_node *current;
    t_command_node *next;

    current = head;
    while (current)
    {
        next = current->next;
        free_command(current->command);
        free(current);
        current = next;
    }
}

void free_command(t_command *command)
{
    free(command->name);
    free_strtokens(command->args);
    free(command);
}
