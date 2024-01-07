#ifndef PARSING_H
#define PARSING_H

#include "../Libft/libft.h"


// Define any structs or classes for parsing
typedef enum e_token_type
{
    WORD,
    PIPE,
    REDIRECT_IN,
    REDIRECT_OUT,
    APPEND,
    HEREDOC,
    ENV_VAR,
    QUOTE,
    DQUOTE,
    QUOTED_ELEMENT,
    DOLLAR,
    INVALID
} t_token_type;

typedef struct s_token
{
    t_token_type type;
    char* value;
} t_token;

typedef struct s_token_node
{
    t_token* token;
    struct s_token_node* next;
} t_token_node;

typedef struct s_command
{
    char* name;
    char** args;
} t_command;

typedef struct s_command_node
{
    t_command* command;
    struct s_command_node* next;
} t_command_node;

// Declare any function prototypes for parsing

t_command_node *command_split(char const *line);
t_command_node *create_new_command_node(char *value);
t_command *parse_command(char *value);
void free_command_list(t_command_node *head);
void free_command(t_command *command);


#endif // PARSING_H
