
#include "../includes/minishell.h"

char	**free_split_get_env(char **env2, char **env)
{
	free_split(env2);
	env2 = get_env(env);
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

char	**unset_each(char *av, char **env, int len, int j)
{
	int		i;
	char	**env2;

	i = 0;
	env2 = calloc(sizeof(char *), env_size(env));
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

char	**unset(char **av, char **env)
{
	char	**env2;
	int		len;
	int		j;
	int		k;

	j = 0;
	k = 0;
	env2 = get_env(env);
	while (av[k])
	{
		if (av[k] == NULL)
		{
			free_split(env);
			k++;
		}
		else
		{
			len = 0;
			env2 = unset_each(av[k], env2, len, j);
			k++;
		}
	}
	free_split(env);
	return (env2);
}
