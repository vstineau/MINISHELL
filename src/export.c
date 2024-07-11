
#include "../includes/minishell.h"

char	**ft_print_export(char **env, int fd)
{
	int		i;
	char	**env2;
	int		len;

	len = env_size(env);
	i = 0;
	env2 = get_env(env);
	ft_sort_strings(len, env);
	while (env[i])
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(env[i], fd);
		ft_putstr_fd("\n", fd);
		i++;
	}
	if (fd != 1)
		close (fd);
	return (env2);
}

char	*get_first_av(char *av)
{
	char	*av1;
	int		i;
	int		len;

	i = 0;
	if (ft_strchr(av, '=') == NULL)
		return (av);
	len = ft_strlen(av);
	while (av[i] != '=' && i < len)
		i++;
	av1 = malloc(sizeof(char) * i + 1);
	i = 0;
	while (av[i + 1] != '=')
	{
		av1[i] = av[i];
		i++;
	}
	av1[i] = av[i];
	av1[i+1] = '\0';
	return (av1);
}

char	**our_export(char **av, char **env, int fd)
{
	char *av1;
	int	i;
	int	len;
	int j;
	char **env2;

	j = 0;
	i = 0;
	len = 0;
	env2 = NULL;
	if (av[0] == NULL)
		return (ft_print_export(env, fd));
	av1 = get_first_av(av[0]);
	if (av1 == NULL)
		return (env2 = get_env(env));
	len = ft_strlen(av1);
	while (env[i])
	{
		if (ft_strncmp(env[i], av1, len) == 0)
		{
			j = env_size(env);
			len = ft_strlen(av[0]);
			env2 = ft_calloc(sizeof(char *), (j + 1));
			j = 0;
			while (env[j])
			{
				if (i != j)
					env2[j] = ft_strdup(env[j]);
				j++;
			}
			env2[i] = ft_strdup(av[0]);
			free(av1);
			return (env2);
		}
		if (ft_strncmp(env[i], av1, len) != 0)
			j++;
		i++;
	}
	if (j == i)
	{
		env2 = ft_calloc(sizeof(char *), (i + 2));
		i = 0;
		while (env[i])
		{
			env2[i] = ft_strdup(env[i]);
			i++;
		}
		env2[i] = ft_strdup(av[0]);
		free(av1);
		return (env2);
	}
	return (env);
}

/*int	main(int ac, char **av, char **env)
{
    (void)ac;
    int i = 0;
	//
	//while (env[i])
	//{
	//	printf("%s\n", env[i]);
	//	i++;
	//}
	char **e = export(av, env);
	i = 0;
	printf("/_____________________________\n");
	while (e[i])
	{
	//	printf("%s\n", e[i]);
		free(e[i]);
		i++;
	}
	free (e);
}*/
