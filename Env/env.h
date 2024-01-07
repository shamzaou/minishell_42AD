#ifndef ENV_H
# define ENV_H

typedef struct s_env_var
{
	char				*key;
	char				*value;
	struct s_env_var	*next;
}						t_env_var;


t_env_var				*env_var_new(char *key, char *value);
int						env_var_update_value(t_env_var *env_var_list,
							t_env_var *new_nod);
void					env_var_insert_sorted(t_env_var **env_var_list,
							t_env_var *new_node);
void					init_env_var_list(char **envp,
							t_env_var **env_var_list);
char					*getenv_value(char *key, t_env_var *env_var_list);



void					free_env_var_node(t_env_var *node);
void					free_env_var_list(t_env_var *env_var_list);
char					*getenv_value(char *key, t_env_var *env_var_list);

#endif