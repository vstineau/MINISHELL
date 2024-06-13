
#include "../includes/minishell.h"

char	*infile(char *s, t_cmd *c)
{
	char key[4096];
	char *line;
	int i;

	i = 0;
	if (*s && *s + 1 == '\0')
		return (s); // exit syntax error:
	if(*s && *(s + 1) == '<')
	{
		s += 2;
		while(*s == ' ')
			s++;
		c->redirect = HEREDOC;
		while ( *s && *s != ' ')
		{
			key[i++] = *s++;
		}
		line = readline(BHI_BLACK"> "RESET);
		while (ft_strcmp(key, line))
		{
			printf("key = %s, line = %s\n", key, line);
			//use open and write to write heredoc in a temporary file
		}
	}
	else
	{
		c->redirect = NO_HEREDOC;
		while (*s == ' ' && *s)
			s++;
		while (*s != ' ' && *s)
		{
			c->infile = s;
			c->infile++;
			s++;
		}
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
