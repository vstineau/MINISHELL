
#include "../includes/minishell.h"

static int	get_outfile(char *s, t_cmd *c, t_minishell *info)
{
	int	i;
	int	j;

	if (c->outfile)
		free(c->outfile);
	c->outfile = ft_calloc(ft_strlen(s) + 1, 1);
	if (!c->outfile)
		exit_free_perror(c, ENV, info,
			BG_RED"memory allocation failed during parsing"RESET);
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
	if (*s && *(s + 1) == '\0')
	{
		info->code_error = 2;
		c->error = 1;
		return (1);
	}
	if (*s && *(s + 1) == '<')
	{
		i += 2;
		c->redirect = HEREDOC;
		if (*(s + 2) && *(s + 2) == '<')
			c->error = 1;
		if (!c->error)
			i += heredoc(s + i, c, info, s);
	}
	else
	{
		i++;
		c->redirect = NO_HEREDOC;
		i += no_heredoc(s + i, c, info);
	}
	return (i);
}

int	outfile(char *s, t_cmd *c, t_minishell *info)
{
	int	i;

	i = 0;
	if (*s && *(s + 1) == '\0')
	{
		info->code_error = 2;
		c->error = 1;
		return (1);
	}
	if (*s && *(s + 1) == '>')
	{
		if (*(s + 2) && *(s + 2) == '>')
			c->error = 1;
		i += 2;
		c->redirect = APPEND;
	}
	else
	{
		i++;
		c->redirect = NO_APPEND;
	}
	i += get_outfile(s + i, c, info);
	return (i);
}
