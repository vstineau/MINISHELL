
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
