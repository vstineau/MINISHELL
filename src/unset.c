
#include "../includes/minishell.h"

char	**unset(char *av, char **env)
{
	char	**env2;
	int		i;
	int		len;
	int		j;

	j = 0;
	env2 = NULL;
	i = 0;
	len = ft_strlen(av);
	while (env[i])
	{
		if (ft_strncmp(env[i], av, len) == 0)
		{
			env2 = calloc(sizeof(char *), env_size(env)); 
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
			return (env2);
		}
		i++;
	}
	if (i == env_size(env))
		env2 = get_env(env);
	return (env2);
}

/*int	main(int ac, char **av, char **env)
{
	(void)ac;
    int i = 0;

	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	char **e = unset(av[1], env);
	i = 0;
	printf("/_____________________________\n");
	while (e[i])
	{
		printf("%s\n", e[i]);
		free(e[i]);
		i++;
	}
	free (e);
}*/
