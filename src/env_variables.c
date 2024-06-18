
#include "../includes/minishell.h"

static char *get_env_variable(char *var, char **envp)
{
	int	i;
	int	j;
	char	*h;

	i = 0;
	h = NULL;
	while(envp[i])
	{
		printf("arg = %s\n", envp[i]);
	 j = 0;
		if (envp[i][j] == var[j])
		{
			while(envp[i][j] == var[j])
				j++;
			if (envp[i][j] && envp[i][j] != '=')
			{
				h = ft_calloc(ft_strlen(envp[i] + j) + 1, 1);
				if (!h)
					return (NULL);
				ft_strcpy(h, envp[i] + j);
				return (h);
			}
		}
		i++;
	}
	free(h);
	return (NULL);
}

int	env_variables(char *s, char **envp, t_cmd *c, int i)
{
	int	j;
	char	key[4096];

	j = 1;
	ft_memset(key, 0, 4096);
	while (s[j] && s[j] != ' ')
	{
		key[j - 1] = s[j];
		printf("key[j] = %c\n", key[j]);
		j++;
	}
	key[j - 1] = '=';
	c->arg[i] = get_env_variable(key, envp);
	if (!c->arg[i])
		return (0); // exit error
	printf("arg = %s\n", c->arg[i]);
	return (j);
}
