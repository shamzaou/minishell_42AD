#include "../minishell.h"

void	remove_empty_args(t_execcmd *ecmd)
{
	int	i;

	while (ecmd->av[0] && ecmd->av[0][0] == '\0')
	{
		i = 0;
		while (ecmd->av[i] && ecmd->av[i + 1])
		{
			ecmd->av[i] = ecmd->av[i + 1];
			i++;
		}
		ecmd->av[i] = NULL;
	}
}

void	handle_invalid_executable(t_execcmd *ecmd, t_params *params,
	struct stat path_stat)
{
	if (S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd1("minishell: ", ecmd->av[0], ": is a directory\n",
			STDERR_FILENO);
		free_exit(params, 126);
	}
	else if (access(ecmd->av[0], X_OK) != 0)
	{
		ft_putstr_fd1("minishell: ", ecmd->av[0], ": Permission denied\n",
			STDERR_FILENO);
		free_exit(params, 126);
	}
}

void	handle_executable_path(t_execcmd *ecmd, t_params *params)
{
	struct stat	path_stat;

	if (ecmd->av[0] == NULL)
		free_exit(params, 0);
	else if (ft_strchr("./", ecmd->av[0][0]))
	{
		if (stat(ecmd->av[0], &path_stat) == 0)
			handle_invalid_executable(ecmd, params, path_stat);
		else
		{
			ft_putstr_fd1("minishell: ", ecmd->av[0],
				": No such file or directory\n", STDERR_FILENO);
			free_exit(params, 127);
		}
	}
}

char	*find_command_path(char *cmd, char *path_var)
{
	int		i;
	char	**paths;
	char	*command;
	char	*binary_path;

	paths = ft_split(path_var, ':');
	command = ft_strjoin("/", cmd);
	i = 0;
	while (paths[i])
	{
		binary_path = ft_strjoin(paths[i], command);
		if (access(binary_path, X_OK) == 0)
		{
			ft_free(command);
			free_split(paths);
			return (binary_path);
		}
		ft_free(binary_path);
		i++;
	}
	ft_free(command);
	free_split(paths);
	return (NULL);
}
