
#include "../includes/minishell.h"

t_cmd	*parse(char *s)
{
	t_cmd *c;

	c = (t_cmd *){0};
	c->first = c;
	while (*s != '\0')
	{
		if ((*s == '<' && *(s + 1) != '<') || (*s == '>' && *(s + 1) != '>'))
			infile(s, &c);
		else if ((*s == '>' && *(s + 1) == '>') || (*s == '<' && *(s + 1) == '<'))
			;
		else if (*s == '"')
			;
		else if (*s == '\'')
			;
		else if (*s == '|')
			c = c->next;
		s++;
	}
	return (c->first);
}
