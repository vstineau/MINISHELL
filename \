
#include "../includes/minishell.h"

static int	if_cmd(char *s, t_cmd *c, int *i_arg)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[j] && (s[j] == ' ' || s[j] == '\t'))
		j++;
	while (s[i + j] && s[i + j] != ' ' && s[i + j] != '\t')
		i++;
	c->arg[*i_arg] = ft_calloc(i + 1, 1);
	if (!c->arg[*i_arg])
		return (0); // error et exit
	i = 0;
	while (s[i + j] && s[i + j] != ' ' && s[i + j] != '\t')
	{
		c->arg[*i_arg][i] = s[i + j];
		i++;
	}
	*i_arg += 1;
	return (i + j);
}

int	get_cmd(char *s, t_cmd *c, int *i_arg)
{
	int i;
	int j;

	if (!c->cmd)
	{
		j = 0;
		i = 0;
		while (s[j] && (s[j] == ' ' || s[j] == '\t'))
			j++;
		while (s[i + j] && s[i + j] != ' ' && s[i + j] != '\t')
			i++;
		c->cmd = ft_calloc(i + 1, 1);
		if (!c->arg)
			return (0); // error et exit
		i = 0;
		while (s[j + i] && s[j + i] != ' ' && s[i + j] != '\t')
		{
			c->cmd[i] = s[i + j];
			i++;
		}
		return (i);
	}
	else
	{
		return (if_cmd(s, c, i_arg));
	}
}
