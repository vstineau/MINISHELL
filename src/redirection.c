
#include "../includes/minishell.h"

void	infile(char *s, t_cmd **c)
{
	if(++*s == '<')
	{
		(*c)->redirect = HEREDOC;
		while (*s != 'n' && *s)
		{
			(*c)->heredoc = s;
			s++;
			(*c)->heredoc++;
		}
		while (*s != 'n' && *s)
		{
			(*c)->infile = s;
			s++;
			(*c)->infile++;
		}
	}
	else
	{
		(*c)->redirect = NO_HEREDOC;
		while (*s == ' ' && *s)
			s++;
		while (*s != ' ' && *s)
		{
			(*c)->infile = s;
			s++;
			(*c)->infile++;
		}
	}
}

void	outfile(char *s, t_cmd **c)
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
}
