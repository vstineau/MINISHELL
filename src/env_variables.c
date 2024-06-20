
#include "../includes/minishell.h"

//char	*new_env_variable(char *var)
//{
//	int	i;
//	int	l;
//	char	*s;
//
//	i = 0;
//	l = ft_strlen(var);
//	s = NULL;
//	s = ft_calloc(1, l);
//	if (!s)
//		return (NULL); // free exit error
//	while (i < l - 1)
//	{
//		s[i] = var[i];
//		i++;
//	}
//	return (s);
//}
//
char *get_env_variable(char *var, char **envp)
{
	int	i;
	int	j;
	char	*h;

	i = 0;
	h = NULL;
	while(envp[i])
	{
	 j = 0;
		if (envp[i][j] == var[j])
		{
			while(envp[i][j] == var[j])
				j++;
			if (envp[i][j] && envp[i][j] != '=')
			{
				h = ft_calloc(ft_strlen(envp[i] + j) + 1, 1);
				if (!h)
					return (NULL); // exit error free
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
		j++;
	}
	key[j - 1] = '=';
	c->arg[i] = get_env_variable(key, envp);
	if (!c->arg[i])
	{
		;//exit error free
		//c->arg[i] = new_env_variable(key);
	}
	return (j);
}
