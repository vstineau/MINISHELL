
#include "../includes/minishell.h"


t_cmd	*parse(char *s)
{
	t_cmd *c;
	int	i;

	c = (t_cmd *){0};
	i = 0;
	while (s[i])
	{
		if (s[i] == '|')
			;
		if (s[i] == '<' && s[i + 1] != '<')
			;
		if (s[i] == '>' && s[i + 1] != '>')
			;
		if (s[i] == '>' && s[i + 1] == '>')
			;
		if (s[i] == '<' && s[i + 1] == '<')
			;
		if (s[i] == '"')
			;
		if (s[i] == '\'')
			;
	}
}
