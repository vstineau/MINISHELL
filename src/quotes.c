
#include "../includes/minishell.h"

int	len_quote(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

int	single_quotes(char *s, t_cmd *c, int i)
{
	int	j;
	int	k;

	j = 1;
	k = 0;
	c->arg[i] = ft_calloc(len_quote(s + j, '\'') + 1, 1);
	if (!c->arg[i])
		return (0); // error et exit
	while (s[j] && s[j] != '\'')
		c->arg[i][k++] = s[j++];
	j++;
	return (j);
}
