
#include "../includes/minishell.h"

static int	get_outfile(char *s, t_cmd *c)
{
	int	i;
	int	j;

	c->outfile = ft_calloc(ft_strlen(s) + 1, 1);
	if (!c->outfile)
		return (0); // print error et exit
	i = 0;
	j = 0;
	while (s[i] && s[i] == ' ')
		i++;
	while (s[i] && s[i] != ' ')
		c->outfile[j++] = s[i++];
	return (i);
}

int	infile(char *s, t_cmd *c, t_minishell *info)
{
	int	i;

	i = 0;
	printf("line = %s\n", s);
	if (*s && *s + 1 == '\0')
	{
		free_cmd(c, ENV, info);
		perror(HIBG_RED"syntax error"RESET);
		exit(1);
	}
	if(*s && *(s + 1) == '<')
	{
		i += 2;
		c->redirect = HEREDOC;
		i += heredoc(s + i, c);
	}
	else
	{
		i++;
		c->redirect = NO_HEREDOC;
		i += no_heredoc(s + i, c);
	}
	return (i);
}

int	outfile(char *s, t_cmd *c)
{
	int	i;

	i = 0;
	if (*s && *s + 1 == '\0')
		return (0); // exit syntax error:
	if (*s && *(s + 1) == '>')
	{
		i += 2;
		c->redirect = APPEND;
	}
	else
	{
		i++;
		c->redirect = NO_APPEND;
	}
	i += get_outfile(s + i, c);
	return (i);
}
