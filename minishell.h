#ifndef MINISHELL_H
# define MINISHELL_H

#include "Libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include <curses.h>
#include <term.h>
#include <readline/readline.h>
#include <readline/history.h>

# define PROMPT "minishell-$>"

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
    DOLLAR,
    INVALID
}           t_token_type;

typedef struct s_tokens
{
    t_token_type        type;
    char                *value;
    struct s_tokens     *next;
    struct s_tokens     *prev;
}       t_tokens;

typedef struct s_data
{

}       t_data;


/* >>> tokeniser.c <<< */
t_tokens            *tokenise(char const *line);
t_tokens            *create_new_token(char *value);
t_tokens            *classify(char **strtokens);
void                free_strtokens(char **strtokens);
t_token_type        get_type(char *value);
void                clear_tokens(t_tokens *head);

/* >>> utils.c <<< */
int     ft_strcmp(char *s1, char *s2);
char	**ft_splitter(char const *s, char c);
char    *ft_strtolower(char *str);

#endif