/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstineau <vstineau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:54:37 by vstineau          #+#    #+#             */
/*   Updated: 2024/08/09 17:50:40 by aroualid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*wrong_identifier(char *av, t_cmd *c, char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(av, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	c->i->code_error = 2;
	return (NULL);
}

char	**export_first_case(char**env, int i, char *av1, char *av)
{
	char	**env2;
	int		j;
	char	*test;

	env2 = ft_calloc(sizeof(char *), env_size(env) + 1);
	j = 0;
	while (env[j])
	{
		if (i != j)
			env2[j] = ft_strdup(env[j]);
		j++;
	}
	test = ft_strchr(av, '+');
	if (test != NULL && test[1] == '=')
	{
		test = ft_strchr(test, test[2]);
		test = ft_strjoin(env[i], test);
		env2[i] = ft_strdup(test);
	}
	else
		env2[i] = ft_strdup(av);
	free(test);
	free(av1);
	free_split(env);
	return (env2);
}

char	**export_second_case(char **env, int i, char *av1, char *av)
{
	char	**env2;
	char	*test;

	(void) av;
	env2 = ft_calloc(sizeof(char *), (i + 2));
	i = 0;
	while (env[i])
	{
		env2[i] = ft_strdup(env[i]);
		i++;
	}
	test = ft_strchr(av1, '+');
	if (test != NULL && test[1] == '=')
	{
		test = ft_strchr(test, '=');
		test = ft_strjoin(av1, test);
		env2[i] = ft_strdup(test);
	}
	else
		env2[i] = ft_strdup(av1);
	free(test);
	free(av1);
	free_split(env);
	return (env2);
}

char	**export_each(char **env, char *av1, int len, char *av)
{
	char	**env2;
	int		i;
	int		j;

	j = 0;
	i = 0;
	env2 = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], av1, len) == 0)
			return (env2 = export_first_case(env, i, av1, av));
		if (ft_strncmp(env[i], av1, len) != 0)
			j++;
		i++;
	}
	if (j == i)
		return (env2 = export_second_case(env, i, av1, av));
	free(av1);
	free_split(env2);
	return (env);
}

char	**our_export(char **av, char **env, int fd, t_cmd *c)
{
	char	*av1;
	int		len;
	char	**env2;
	int		k;

	k = 0;
	len = 0;
	env2 = get_env(env, NULL, 0);
	if (av[0] == NULL)
		return (free_split(env), ft_print_export(env2, fd));
	while (av[k])
	{
		av1 = get_first_av(av[k], c);
		if (av1 == NULL)
			k++;
		else
		{
			len = ft_strlen(av1);
			env2 = export_each(env2, av1, len, av[k]);
			k++;
		}
	}
	free_split(env);
	return (env2);
}
