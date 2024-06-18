
#include "../includes/minishell.h"

static int	if_cmd(char *s, t_cmd *c, int *i_arg)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != ' ')
		i++;
	c->arg[*i_arg] = ft_calloc(i + 1, 1);
	if (!c->arg)
		return (0); // error et exit
	i = 0;
	while (s[i] && s[i] != ' ')
	{
		c->arg[*i_arg][i] = s[i];
		i++;
	}
	return (i);
}

int	get_cmd(char *s, t_cmd *c, int *i_arg)
{
	int i;

	i = 0;
	if (c->cmd)
	{
		while (s[i] && s[i] != ' ')
			i++;
		c->cmd = ft_calloc(i + 1, 1);
		if (!c->arg)
			return (0); // error et exit
		i = 0;
		while (s[i] && s[i] != ' ')
		{
			c->cmd[i] = s[i];
			i++;
		}
		return (i);
	}
	else
		return (if_cmd(s, c, i_arg));
}
