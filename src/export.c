
#include "../includes/minishell.h"

int	ft_strncmp( const char *first, const char *second, size_t length)
{
	unsigned int	i;

	i = 0;
	if (length == 0)
		return (0);
	while (first[i] == second[i] && i < length - 1 && first[i])
	{
		i++;
	}
	return (((unsigned char *)first)[i] - ((unsigned char *)second)[i]);
}

char	*get_first_av(char *av)
{
	char	*av1;
	int		i;

	i = 0;
	while (av[i] != '=')
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

int	env_size(char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char **export(char **av, char **env)
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
	av1 = get_first_av(av[1]);
	len = ft_strlen(av1);
	while (env[i])
	{
		if (ft_strncmp(env[i], av1, len) == 0)
		{
			j = env_size(env);
			len = ft_strlen(av[1]);
			env2 = ft_calloc(sizeof(char *), (j + 1));
			j = 0;
			while (env[j])
			{
				if (i != j)
					env2[j] = ft_strdup(env[j]);
				j++;
			}
			env2[i] = ft_strdup(av[1]);
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
		env2[i] = ft_strdup(av[1]);
		free(av1);
		return (env2);
	}
	return (env);
}

int	main(int ac, char **av, char **env)
{
    (void)ac;
    int i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	printf("/_____________________________\n");
	char **e = export(av, env);
	i = 0;
	while (e[i])
	{
		printf("%s\n", e[i]);
		free(e[i]);
		i++;
	}
	free (e);
}
