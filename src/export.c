
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
			len = ft_strlen(av[1]);
			ft_realloc(env[i], ft_strlen(env[i]), len);
			ft_strcpy(env[i], av[1]);
			free(av1);
			return (env);
		}
		if (ft_strncmp(env[i], av1, len) != 0)
			j++;
		i++;
	}
	if (j == i)
	{
		printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
		env2 = ft_calloc(sizeof(char *), (i + 1));
		i = 0;
		while (env[i])
		{
			env2[i] = ft_strdup(env[i]);
			i++;
		}
		free_split(env);
		env2[i] = ft_strdup(av[1]);
	}
	free(av1);
	return (env2);
}

int	main(int ac, char **av, char **env)
{
    (void)ac;
    int i = 0;
	printf("%s\n", av[1]);
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	printf("/---------------------------------------------------------\n");
	char **e = get_env(env);
	export(av, e);
	i = 0;
	while (e[i])
	{
		printf("%s\n", e[i]);
		i++;
	}
}
