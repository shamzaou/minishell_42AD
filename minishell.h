#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define PROMPT "minishell-$>"
# define EXEC 1
# define REDIR 2
# define PIPE 3
# define MAXARGS 1024

/* >>>> data structures <<<< */

typedef struct s_cmd
{
	int							type;
}								t_cmd;

typedef struct s_pipecmd
{
	int							type;
	t_cmd						*right;
	t_cmd						*left;
}								t_pipecmd;

typedef struct s_execcmd
{
	int							type;
	char						*av[MAXARGS];
	char						*eargv[MAXARGS];
}								t_execcmd;

typedef struct s_redircmd
{
	int							type;
	char						*file;
	char						*efile;
	int							fd;
	char						r_type;
	int							mode;
	t_cmd						*subcmd;
}								t_redircmd;

typedef struct s_redirdata
{
	char						*file;
	char						*efile;
	int							fd;
	int							mode;
}								t_redirdata;

typedef struct s_env_var
{
	char						*key;
	char						*value;
	struct s_env_var			*next;
}								t_env_var;

typedef struct s_queue_node
{
	void						*val;
	struct s_queue_node			*next;
}								t_queue_node;

typedef struct s_queue
{
	t_queue_node				*front;
	t_queue_node				*rear;
}								t_queue;

typedef struct s_char_queue
{
	struct s_char_queue_node	*front;
	struct s_char_queue_node	*rear;
}								t_char_queue;

struct							s_char_queue_node
{
	char						val;
	struct s_char_queue_node	*next;
};

typedef struct s_params
{
	char						*buf;
	char						**envp;
	t_env_var					*env_var_list;
	t_cmd						*tree;
	t_queue						args_queue;
}								t_params;

/**
 * PARSING
*/

/* >>>> syntax_analyzer.c && syntax_analyzer_helpers.c <<<< */

int								validate_command(char *buf, int *exit_status);
int								check_invalid_pipe_syntax(char **ps, char *es,
									int *exit_status);
int								validate_redirection(char **ps, char *es,
									int *exit_status);
int								validate_pipe(char **ps, char *es,
									int *exit_status);
int								peek(char **ps, char *es, char *tokens);
int								get_next_token(char **ps, char *es, char **q,
									char **eq);

/* >>>> parsing.c && parse_exec.c && tokenise.c <<<< */

t_cmd							*parse_cmd(char *buf, int *exit_status);
t_cmd							*parse_pipe(char **ps, char *es, int *error);
t_cmd							*parse_exec(char **ps, char *es, int *error);
t_cmd							*parse_redir(t_cmd *subcmd, char **ps,
									char *es);

/* >>>> null_terminate.c <<<< */

t_cmd							*null_terminate_command(t_cmd *cmd);

/* >>>> get_arguments.c && get_arguments_helpers.c <<<< */

void							handle_cmd_args(t_cmd *cmd, t_params *params,
									int *exit_status);
int								contains_special_char(char *arg);
char							*getvar_name(char *arg);

/* >>>> quotes.c && dollar.c <<<< */

void							get_quote(char *arg, int *i, t_char_queue *q);
void							handle_dquotes_envar(int *values[2], char *arg,
									t_char_queue *q, t_params *params);
void							handle_dquotes_exitstatus(int *values[2],
									t_char_queue *q);
void							handle_dquotes(int *values[2], char *arg,
									t_char_queue *q, t_params *params);
void							handle_env_dollar(int *values[2],
									t_char_queue *q, char *arg,
									t_params *params);
void							handle_dollar(int *values[2], t_char_queue *q,
									char *arg, t_params *params);

/* >>>> broomstick.c <<<< */

void							free_tree(t_cmd *cmd);

/**
 * EXECUTION
*/

/* >>>> exec.c <<<< */

void							run_exec(t_cmd *cmd, t_params *params,
									int *exit_status);

/* >>>> exec_cmd.c <<<< */

void							run_cmd(t_cmd *cmd, t_params *params,
									int *exit_status);

/* >>>> exec_pipe.c && exec_pipe_helpers.c <<<< */

void							run_pipe(t_cmd *cmd, t_params *params,
									int *exit_status);
void							execute_left_subtree(t_cmd *cmd, int fd[2],
									t_params *params, int *exit_status);
void							execute_right_subtree(t_cmd *cmd, int fd[2],
									t_params *params, int *exit_status);
void							write_exit_status_to_file(t_params *params,
									int exit_status);

/* >>>> exec_redir.c <<<< */

void							run_redir(t_cmd *cmd, t_params *params,
									int *exit_status);
char							*process_quoted_filename(char *file);

/* >>>> exec_utils.c <<<< */

void							remove_empty_args(t_execcmd *ecmd);
void							handle_invalid_executable(t_execcmd *ecmd,
									t_params *params, struct stat path_stat);
void							handle_executable_path(t_execcmd *ecmd,
									t_params *params);
char							*find_command_path(char *cmd, char *path_var);

/* >>>> exec_builtin.c <<<< */

int								is_builtin_command(t_execcmd *ecmd);
void							execute_builtin_commands(t_execcmd *ecmd,
									t_params *params, int exit_status);

/* >>>> operators.c <<<< */

t_cmd							*pipecmd(t_cmd *left, t_cmd *right);
t_cmd							*execcmd(void);
t_redirdata						redirdata(char *file, char *efile, int mode,
									int fd);
t_cmd							*redircmd(t_cmd *subcmd, t_redirdata data,
									char r_type);

/* >>>> toolbox0.c <<<< */

int								is_built_in_command(t_cmd *tree);
void							execute_built_in_command(t_execcmd *ecmd,
									t_env_var **env_var_list, int *exit_status);
void							save_child_pid(int pid, t_params *params);
void							get_exit_status(t_cmd *tree, t_params *params,
									int *exit_status, int status);
void							cleanup(t_params *params);

/* >>>> toolbox1.c <<<< */

int								is_whitespace(char c);
int								is_whitespace_string(char *str);
int								is_numeric(const char *str);
int								forking(t_params *params);
void							pipe1(int fd[2], t_params *params);

/* >>>> ft_free.c <<<< */

void							ft_free(void *ptr);
void							free_split(char **array);
void							free_exit(t_params *params, int exit_status);
void							free_panic_exit(t_params *params, char *error,
									int exit_status);

/* >>>> queue.c <<<< */

void							init_queue(t_queue *q);
void							add_to_queue(t_queue *q, void *val);
void							*pop_queue(t_queue *q);
char							*queue_to_str(t_queue *q);
void							free_queue(t_queue *q);
void							init_queue_char(t_char_queue *q);
void							add_char_to_queue(t_char_queue *q, char c);
void							add_string_to_char_queue(t_char_queue *q,
									char *str);
char							pop_char_from_queue(t_char_queue *q);
char							*char_queue_to_str(t_char_queue *q);

/**
 * BUILTINS FOLDER
*/

void							cd(char **av, int *exit_status,
									t_env_var *env_var_list);
void							echo(char **av);
void							env(char **av, t_params *params);
void							exit_command(char **av, t_params *params);
void							export(char **args, t_env_var *env_var_list);
void							export_command(char **args,
									t_env_var **env_var_list, int *exit_status);
void							pwd(int *exit_status);
void							unset_env_var(char **args,
									t_env_var **env_var_list, int *exit_status);

int								is_valid_variable_name(char *key);
char							*extract_variable_name(char *arg,
									char *equal_sign);

/**
 * ENVIRONMENT
*/

t_env_var						*env_var_new(char *key, char *value);
int								env_var_update_value(t_env_var *env_var_list,
									t_env_var *new_nod);
void							env_var_insert_sorted(t_env_var **env_var_list,
									t_env_var *new_node);
void							init_env_var_list(char **envp,
									t_env_var **env_var_list);
void							free_env_var_node(t_env_var *node);
void							free_env_var_list(t_env_var *env_var_list);
char							*getenv_value(char *key,
									t_env_var *env_var_list);

/**
 * SIGNALS
*/
/* >>>> signals.c <<<< */
void							signal_handler(int signum);
void							signal_handler_herdoc(int signum);
void							signal_handler_input(int signum);
void							setup_signals(void);
void							set_signal_handler(t_cmd *tree);

#endif