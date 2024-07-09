
#include "../includes/minishell.h"

int	len_quote(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

int	expand_doubles_quotes(t_iterator *a, char *line)
{
	if (a->doubles_quotes)
		a->doubles_quotes = false;
	else
		a->doubles_quotes = true;
	line[a->j] = '"';
	a->i++;
	return (1);
}

int	expand_single_quotes(t_iterator *a, char *line)
{
	if (a->single_quotes)
		a->single_quotes = false;
	else
		a->single_quotes = true;
	line[a->j] = '\'';
	a->i++;
	return (1);
}

int	single_quotes(char *s, t_cmd *c, int i, int k)
{
	int	j;

	j = 1;
	while (s[j] && s[j] != '\'')
		c->arg[i][k++] = s[j++];
	j++;
	return (j);
}

int	double_quotes(char *s, t_cmd *c,char **envp, int *i)
{
	int	j;
	char *e_var;
	char key[4096];

	j = 1;
	e_var = NULL;
	ft_memset(key, 0, 4096);
	c->arg[*i] = ft_calloc(len_quote(s + j, '"') +1 , 1);
	if (!c->arg[*i])
		return (0);
	while (s[j] && s[j] != '"')
	{
		if (s[j] == '$')
		{
			ft_strncpy(key, s + j + 1, len_quote(s + j + 1, ' '));
			key[len_quote(s + j + 1, ' ')] = '=';
			e_var = get_env_variable(key, envp);
			c->arg[*i] = ft_strjoin_free(c->arg[*i], e_var);
			free(e_var);
			i++;
		}
		else
			c->arg[*i][j - 1] = s[j];
		j++;
	}
	*i += 1;
	return (j);
}
