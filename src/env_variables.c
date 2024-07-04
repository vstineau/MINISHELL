#include "../includes/minishell.h"

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

int	expand_env_v(char *s, char *line, t_minishell *info, t_iterator *a)
{
	int	j;
	char	key[4096];
	char *var;

	j = 1;
	var = NULL;
	ft_memset(key, 0, 4096);
	while (s[j] && check_char(s[j], " \t"))
	{
		key[j - 1] = s[j];
		j++;
	}
	key[j - 1] = '=';
	var = get_env_variable(key, info->env);
	if (!var)
		return (0);
	else
	{
		line = ft_realloc(line, ft_strlen(line), ft_strlen(line) + ft_strlen(var) + 1);
		if (line == NULL)
		{
			free_cmd(NULL, ENV, info);
			perror(BG_RED"memory allocation failed during parsing"RESET);
			exit(1);
		}
		ft_memcpy(line + a->j, var, ft_strlen(var));
	}
	a->i += j;
	free(var);
	return (ft_strlen(var));
}
