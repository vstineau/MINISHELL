
#include "../includes/minishell.h"

void	single_quotes(char *s, t_cmd **c, int i)
{
	while (++*s != '\'')
	{
		if (*s == '\0')
			return; // free error
		*(*c)->arg[i]++ = *s++;
	}
}
