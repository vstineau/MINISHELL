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

int	expand_env_v(char *s, char **line, t_minishell *info, t_iterator *a)
{
	int	j;
	char	key[4096];
	char	*var;
	int	len_var;
	int	len_line;

	len_line = ft_strlen(*line);
	if (len_line < ft_strlen(s))
		len_line = ft_strlen(s);
	j = 1 + a->i;
	var = NULL;
	ft_memset(key, 0, 4096);
	while (s[j] && !check_char(s[j], " \t") && is_uppercase(s[j]))
	{
		key[j - a->i - 1] = s[j];
		j++;
	}
	key[j - a->i - 1] = '=';
	var = get_env_variable(key, info->env);
	if (!var)
		return (0);
	else
	{
		len_var = ft_strlen(var);
		*line = ft_realloc(*line, len_line, len_line + len_var + 1);
		if (*line == NULL)
		{
			free_cmd(NULL, ENV, info);
			perror(BG_RED"memory allocation failed during parsing"RESET);
			exit(1);
		}
		ft_memcpy(*line + a->j, var, len_var);
	}
	a->i += j - a->i;
	free(var);
	return (len_var);
}
