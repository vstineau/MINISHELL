
#include "../includes/minishell.h"

char	*infile(char *s, t_cmd *c)
{
	if (*s && *s + 1 == '\0')
		return (s); // exit syntax error:
	if(*s && *(s + 1) == '<')
	{
		s += 2;
		c->redirect = HEREDOC;
		c->infile = heredoc(s);
	}
	else
	{
		s ++;
		c->redirect = NO_HEREDOC;
		c->infile = no_heredoc(s);
		printf("infile = %s\n",c->infile);
	}
	return (s);
}

char	*outfile(char *s, t_cmd **c)
{
	if (++*s == '>')
		(*c)->redirect = APPEND;
	else
		(*c)->redirect = NO_APPEND;
	while (*s != ' ' && *s)
	{
		(*c)->outfile  = s;
		s++;
		(*c)->outfile++;
	}
	return (s);
}
