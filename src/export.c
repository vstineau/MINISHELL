/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstineau <vstineau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:54:37 by vstineau          #+#    #+#             */
/*   Updated: 2024/08/13 14:44:37 by aroualid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*wrong_identifier(char *av, t_cmd *c, char *cmd)
{
	ft_putstr_fd(cmd, 2, c->i);
	ft_putstr_fd(": `", 2, c->i);
	ft_putstr_fd(av, 2, c->i);
	ft_putstr_fd("': not a valid identifier\n", 2, c->i);
	c->i->code_error = 2;
	return (NULL);
}

char	**export_first_case(char**env, int i, t_cmd *c, int j)
{
	char	**env2;
	char	*test;

	env2 = ft_calloc(sizeof(char *), env_size(env) + 1);
	if (!env2)
		exit_free_perror(c, ENV, c->i, "");
	while (env[j])
	{
		if (i != j)
			env2[j] = ft_strdup(env[j]);
		j++;
	}
	test = ft_strchr(c->xp->av, '+');
	if (test != NULL && test[1] == '=')
	{
		test = ft_strchr(test, test[2]);
		test = ft_strjoin(env[i], test);
		env2[i] = ft_strdup(test);
	}
	else
		env2[i] = ft_strdup(c->xp->av);
	free(test);
	free(c->xp->av1);
	free_split(env);
	return (env2);
}

char	**export_second_case(char **env, int i, t_cmd *c)
{
	char	**env2;
	char	*test;

	env2 = ft_calloc(sizeof(char *), (i + 2));
	if (!env2)
		exit_free_perror(c, ENV, c->i, "");
	i = 0;
	while (env[i])
	{
		env2[i] = ft_strdup(env[i]);
		i++;
	}
	test = ft_strchr(c->xp->av, '+');
	if (test != NULL && test[1] == '=')
	{
		test = ft_strchr(test, '=');
		test = ft_strjoin(c->xp->av1, test);
		env2[i] = ft_strdup(test);
	}
	else
		env2[i] = ft_strdup(c->xp->av);
	free(test);
	free(c->xp->av1);
	free_split(env);
	return (env2);
}

char	**export_each(char **env, t_cmd *c)
{
	char	**env2;
	int		i;
	int		j;
	int		len;

	len = ft_strlen(c->xp->av1);
	j = 0;
	i = 0;
	env2 = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], c->xp->av1, len) == 0 && (env[i][len] == '='))
		{
			j = 0;
			return (env2 = export_first_case(env, i, c, j));
		}
		if ((ft_strncmp(env[i], c->xp->av1, len) != 0) || (env[i][len] != '='))
			j++;
		i++;
	}
	if (j == i)
		return (env2 = export_second_case(env, i, c));
	free(c->xp->av1);
	free_split(env2);
	return (env);
}

char	**our_export(char **av, char **env, int fd, t_cmd *c)
{
	char	**env2;
	int		k;

	k = 0;
	env2 = get_env(env, NULL, 0);
	if (av[0] == NULL)
		return (free_split(env), ft_print_export(env2, fd, c));
	while (av[k])
	{
		c->xp->av1 = get_first_av(av[k], c);
		if (c->xp->av1 == NULL)
			k++;
		else
		{
			c->xp->av = av[k];
			env2 = export_each(env2, c);
			k++;
		}
	}
	free_split(env);
	return (env2);
}
