
#include "../includes/minishell.h"

char	**get_folders_from_path(char **env)
{
	int		i;
	char	**folders;

	i = 0;
	folders = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
		{
			folders = ft_split(env[i] + 5, ':');
			break ;
		}
		i++;
	}
	return (folders);
}

char	*find_path_in_folders(char **folders, char *av)
{
	char	*path;
	char	*endfile;
	char	**cmd;
	int		j;

	path = NULL;
	endfile = NULL;
	cmd = find_cmd(av);
	j = 0;
	if (cmd == NULL)
		return (NULL);
	endfile = ft_strjoin("/", *cmd);
	while (folders[j])
	{
		path = ft_strjoin(folders[j], endfile);
		if (path == NULL)
			return (free_return(cmd, endfile));
		if (access(path, F_OK | X_OK) == 0)
			return (return_path (cmd, endfile, path));
		free(path);
		j++;
	}
	return (free_return(cmd, endfile));
}

char	*path_ok(char *av)
{
	char	**cmd;
	char	*path;

	cmd = find_cmd(av);
	if (cmd == NULL)
		return (NULL);
	path = *cmd;
	if (access(path, F_OK | X_OK) == 0)
	{
		return (path);
	}
	free_split(cmd);
	return (NULL);
}

char	*find_path(char **env, char *av)
{
	char	**folders;
	char	*path;

	if (path_ok(av) == NULL)
	{
		folders = get_folders_from_path(env);
		if (folders == NULL)
		{
			write(2, "command not found : ", 21);
			write(2, av, ft_strlen(av));
			write(2, "\n", 1);
			return (NULL);
		}
		path = find_path_in_folders(folders, av);
		free_split(folders);
		if (path == NULL)
		{
			write(2, "command not found : ", 21);
			write(2, av, ft_strlen(av));
			write(2, "\n", 1);
			return (NULL);
		}
		return (path);
	}
	return (path_ok(av));
}

char	**find_cmd(char *av)
{
	char	**cmd;

	if (av != NULL)
	{	
		cmd = ft_split(av, ' ');
		if (cmd)
			return (cmd);
		else
			return (free_split(cmd), NULL);
	}
	return (NULL);
}
