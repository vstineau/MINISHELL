
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

char	*get_first_av2(char *av)
{
	char	*av1;
	int		i;
	int		len;
	
	i = 0;
	len = ft_strlen(av);
	while (av[i] != '+' && i < len)
		i++;
	av1 = malloc(sizeof(char) * len + 1);
	ft_strncpy(av1, av, i);
	return (av1);
}

char	*get_first_av(char *av)
{
	char	*av1;
	int		i;
	int		len;
	char	*test;

	i = 0;
	len = ft_strlen(av);
	test = ft_strchr(av, '+');
	if (test != NULL && test[1] == '=')
		return (av1 = get_first_av2(av));
	if (ft_strchr(av, '=') == NULL)
	{
		av1 = malloc(sizeof(char) * len + 1);
		ft_strcpy(av1, av);
		return (av1);
	}
	len = ft_strlen(av);
	while (av[i] != '=' && i < len)
		i++;
	av1 = malloc(sizeof(char) * len + 1);
	ft_strncpy(av1, av, i);
	return (av1);
}

char	**export_each(char **env, char *av1, int len, char *av)
{
	char	**env2;
	int		i;
	int		j;
	char	*test;
	
	j = 0;
	i = 0;
	env2 = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], av1, len) == 0)
		{

			env2 = calloc(sizeof(char *), env_size(env) + 1);
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
		test = ft_strchr(av, '+');
		if (test != NULL && test[1] == '=')
		{
			test = ft_strchr(test, '=');
			test = ft_strjoin(av1, test);
			env2[i] = ft_strdup(test);
		}
		else
			env2[i] = ft_strdup(av);
		free(test);
		free(av1);
		free_split(env);
		return (env2);
	}
	free(av1);
	free_split(env2);
	return (env);
}

char	**our_export(char **av, char **env, int fd)
{
	char	*av1;
	int		len;
	char	**env2;
	int		k;

	k = 0;
	len = 0;
	env2 = get_env(env);
	if (av[0] == NULL)
		return (free_split(env), ft_print_export(env2, fd));
	while (av[k])
	{
		av1 = get_first_av(av[k]);
		if (av1 == NULL)
			return (free(av1), free_split(env), env2);
		len = ft_strlen(av1);
		env2 = export_each(env2, av1, len, av[k]);
		k++;
	}
	free_split(env);
	return (env2);
}
