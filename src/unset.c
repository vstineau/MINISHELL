/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstineau <vstineau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:56:41 by vstineau          #+#    #+#             */
/*   Updated: 2024/08/12 10:51:46 by aroualid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**free_split_get_env(char **env2, char **env)
{
	free_split(env2);
	env2 = get_env(env, NULL, 0);
	free_split(env);
	return (env2);
}

char	**apply_unset_each(int j, int i, char **env, char **env2)
{
	while (j < i)
	{
		env2[j] = ft_strdup(env[j]);
		j++;
	}
	while (j < env_size(env) - 1)
	{
		env2[j] = ft_strdup(env[j + 1]);
		j++;
	}
	return (free_split(env), env2);
}

char	**unset_each(char *av, char **env, int len, t_cmd *c)
{
	int		i;
	char	**env2;
	int		j;

	j = 0;
	i = 0;
	env2 = ft_calloc(sizeof(char *), env_size(env));
	if (!env2)
		exit_free_perror(c, ENV, c->i, "");
	while (env[i])
	{
		while (env[i][len] != '=')
			len++;
		if (ft_strncmp(env[i], av, ft_strlen(av)) == 0 && len == ft_strlen(av))
			return (apply_unset_each(j, i, env, env2));
		i++;
		len = 0;
	}
	return (free_split_get_env(env2, env));
}

int	arg_ok_for_unset(char *av)
{
	int	i;
	int	len;

	len = 0;
	i = 1;
	len = ft_strlen(av);
	while (av[i] && i < len)
	{
		if (ft_isalnum(av[i]) == 1 || av[i] == '_' || av[i] == '+')
			i++;
		else
			return (0);
	}
	return (1);
}

char	**unset(char **av, char **env, t_cmd *c)
{
	char	**env2;
	int		len;
	int		k;

	k = 0;
	env2 = get_env(env, NULL, 0);
	while (av[k])
	{
		if (av[k] == NULL || arg_ok_for_unset(av[k]) == 0)
		{
			if (arg_ok_for_unset(av[k]) == 0)
				wrong_identifier(av[k], c, "export");
			k++;
		}
		else
		{
			len = 0;
			env2 = unset_each(av[k], env2, len, c);
			k++;
		}
	}
	free_split(env);
	return (env2);
}
