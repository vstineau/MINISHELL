
#include "../includes/minishell.h"

void	infile(char *s, t_cmd **c)
{
	char *key;
	char *line;

	if (*s + 1 == '\0' || *s + 2 == '\0')
		return ;
	key = NULL;
	if(*s == '<')
	{
		*(*c)->redirect = HEREDOC;
		while (*s != ' ' && *s)
			*key++ = *s++;
		line = readline(BHI_BLACK">"RESET);
		while (ft_strcmp(key, line))
		{
			line = readline(BHI_BLACK">"RESET);
		}
	}
	else
	{
		*(*c)->redirect = NO_HEREDOC;
		while (*s == ' ' && *s)
			s++;
		while (*s != ' ' && *s)
		{
			(*c)->infile = s;
			(*c)->infile++;
			s++;
		}
	}
}

void	outfile(char *s, t_cmd **c)
{
	if (++*s == '>')
		*(*c)->redirect = APPEND;
	else
		*(*c)->redirect = NO_APPEND;
	while (*s != ' ' && *s)
	{
		(*c)->outfile  = s;
		s++;
		(*c)->outfile++;
	}
}
