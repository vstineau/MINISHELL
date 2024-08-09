/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstineau <vstineau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:54:55 by vstineau          #+#    #+#             */
/*   Updated: 2024/08/09 14:57:48 by vstineau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int		j;

	path = NULL;
	endfile = NULL;
	j = 0;
	if (av == NULL)
		return (NULL);
	endfile = ft_strjoin("/", av);
	while (folders[j])
	{
		path = ft_strjoin(folders[j], endfile);
		if (path == NULL)
			return (free_return(endfile));
		if (access(path, F_OK | X_OK) == 0)
			return (return_path (endfile, path));
		free(path);
		j++;
	}
	return (free_return(endfile));
}

char	*path_ok(char *av)
{
	char	*path;

	path = av;
	if (access(path, F_OK) != 0)
		return (NULL);
	if (access(path, X_OK) == 0)
		return (path);
	return (NULL);
}

char	*find_path(char **env, char *av, t_minishell *info)
{
	char	**folders;
	char	*path;

	if (path_ok(av) == NULL)
	{
		if (access(av, F_OK) != 0)
		{
			folders = get_folders_from_path(env);
			if (folders == NULL)
				return (return_find_path(info, av, 127));
			path = find_path_in_folders(folders, av);
			free_split(folders);
			if (path == NULL)
				return (return_find_path(info, av, 127));
			return (path);
		}
		else
			return (return_find_path(info, av, 126));
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
