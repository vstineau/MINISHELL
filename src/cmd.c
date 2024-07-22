
#include "../includes/minishell.h"

static int	cmd_get_quote(char *s, t_cmd *c, int j)
{
	char	quote;
	int	i;

	i = 1;
	if (*s == '\'')
		quote = '\'';
	else
		quote = '"';
	while (s[i] && s[i] != quote)
	{
		c->cmd[j] = s[i];
		i++;
		j++;
	}
	return (i);
}

static int	arg_get_quote(char *s, t_cmd *c, int iarg, int j)
{
	char	quote;
	int	i;

	i = 1;
	if (*s == '\'')
		quote = '\'';
	else
		quote = '"';
	while (s[i] && s[i] != quote)
	{
		c->arg[iarg][j] = s[i];
		printf(BHI_MAGENTA"s[i] = %c "BHI_CYAN" c->arg[i_arg][i] = %c "BHI_GREEN" arg i = %d\n"RESET, s[i], c->arg[iarg][j], j);
		i++;
		j++;
	}
	return (i);
}


static int	if_cmd(char *s, t_cmd *c, int *i_arg)
{
	int	i;
	int	j;

	i = 0;
	while (s[i] && s[i] != ' ' && s[i] != '\t')
		i++;
	printf(BHI_BLUE"I = %d\n"RESET, i);
	c->arg[*i_arg] = ft_calloc(i + 1, 1);
	if (!c->arg[*i_arg])
		return (0); // error et exit
	i = 0;
	j = 0;
	while (s[i] && s[i] != ' ' && s[i] != '\t')
	{
		printf(BHI_WHITE"s[i] = %c\n", s[i]);
		if (s[i] == '\'' || s[i] == '"')
		{
			printf(BHI_RED"C->ARG[I_ARG] = %s\n"RESET, c->arg[*i_arg]);
			i += arg_get_quote(s + i, c, *i_arg, i) + 1;
			j = i - 2;
		}
		else
		{
			c->arg[*i_arg][j] = s[i];
			printf(BHI_MAGENTA"s[i] = %c "BHI_CYAN" c->arg[i_arg][i] = %c "BHI_GREEN" arg i = %d arg j = %d\n"RESET, s[i], c->arg[*i_arg][i], i, j);
			i++;
			j++;
		}
	}
	printf(BHI_RED"C->ARG[I_ARG] = %s\n"RESET, c->arg[*i_arg]);
	*i_arg += 1;
	return (i);
}

int	get_cmd(char *s, t_cmd *c, int *i_arg)
{
	int i;
	int j;

	if (!c->cmd)
	{
		i = 0;
		while (s[i] && s[i] != ' ' && s[i] != '\t')
			i++;
		c->cmd = ft_calloc(i + 1, 1);
		if (!c->arg)
			return (0); // error et exit
		i = 0;
		j = 0;
		while (s[i] && s[i] != ' ' && s[i] != '\t')
		{
			if (s[i] == '\'' || s[i] == '"')
			{
				i += cmd_get_quote(s + i, c, i) + 1;
				j = i - 2;
			}
			else
			{
				c->cmd[j] = s[i];
				i++;
				j++;
			}
		}
		return (i);
	}
	else
		return (if_cmd(s, c, i_arg));
}
