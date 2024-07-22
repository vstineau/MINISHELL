
#include "../includes/minishell.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

char	**ft_print_export(char **env, int fd)
{
	int		i;
	char	**env2;
	int		len;
	int		j;

	j = 0;
	len = env_size(env);
	i = 0;
	env2 = get_env(env);
	ft_sort_strings(len, env);
	while (env[i])
	{
		len = ft_strlen(env[i]);
		ft_putstr_fd("declare -x ", fd);
		while (env[i][j] != '=' && j < len)
		{
			ft_putchar_fd(env[i][j], fd);
			j++;
		}
		j++;
		if (ft_strchr(env[i], '=') != NULL)
		{
			ft_putstr_fd("=", fd);
			ft_putstr_fd("\"", fd);
			while (j < len)
			{
				ft_putchar_fd(env[i][j], fd);
				j++;
			}
			ft_putstr_fd("\"", fd);
		}
		ft_putstr_fd("\n", fd);
		j = 0;
		i++;
	}
	if (fd != 1)
		close (fd);
	free_split(env);
	return (env2);
}

char	*get_first_av(char *av)
{
	char	*av1;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(av);
	if (ft_strchr(av, '=') == NULL)
	{
		av1 = malloc(sizeof(char) * len + 1);
		ft_strcpy(av1, av);
		return (av1);
	}
	len = ft_strlen(av);
	printf("%i\n", len);
	while (av[i] != '=' && i < len)
		i++;
	av1 = malloc(sizeof(char) * len + 1);
	ft_strncpy(av1, av, i);
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
	{
		free(av1);
		return (env);
	}
	len = ft_strlen(av1);
	while (env[i])
	{
		if (ft_strncmp(env[i], av1, len) == 0)
		{
			printf("TEST\n");
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
			free_split(env);
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
		env2[i] = ft_strdup(av1);
		free(av1);
		free_split(env);
		return (env2);
	}
	free(av1);
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
