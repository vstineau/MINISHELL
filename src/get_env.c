/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstineau <vstineau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:55:13 by vstineau          #+#    #+#             */
/*   Updated: 2024/08/09 14:57:48 by vstineau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env_size(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

char	**get_env(char **envp, char **argv, int argc)
{
	int		i;
	char	**new_env;

	(void)argc;
	(void)argv;
	new_env = ft_calloc(env_size(envp) + 1, sizeof(char *));
	if (!new_env)
	{
		perror("parsing error\n");
		exit(1);
	}
	i = 0;
	while (envp[i])
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
		{
			free_split(new_env);
			perror("parsing error\n");
			exit(1);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}
//
//int main(int argc, char *argv[], char *envp[])
//{
//	(void)argc;
//	(void)argv;
//	int i = 0;
//	char **e = get_env(envp);
//	while (e[i])
//	{
//		printf("%s\n", e[i]);
//		i++;
//	}
//	free_split(e);	
//}
