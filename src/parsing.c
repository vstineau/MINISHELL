
#include "../includes/minishell.h"

t_cmd	*ft_lstnew()
{
	t_cmd *new_cmd;

	new_cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!new_cmd)
		return (NULL);
	//new_cmd = (t_cmd *){0};
	return (new_cmd);
}

void	ft_lstadd_back(t_cmd **cmd, t_cmd *new)
{
	t_cmd *current;
	t_cmd *previous;

	if (!new)
		return ;
	if (!*cmd)
	{
		*cmd = new;
		return ;
	}
	current = *cmd;
	while (current)
	{
		previous = current;
		current = current->next;
	}
	previous->next = new;
}


t_cmd	*parse(char *s)
{
	t_cmd *c;
	t_cmd *current;

	c = ft_lstnew();
	current = c;
	while (*s != '\0')
	{
		if (*s == '<')
			s += infile(s, c);
		else if (*s == '>')
			s += outfile(s, c);
		else if (*s == '"')
			;
		else if (*s == '\'')
			;
		else if (*s == '|')
		{
			;
		//	ft_lstadd_back(&c, ft_lstnew());
		//	current = current->next;
		}
		printf("line = %s\n", s);
		s++;
	}
	return (c);
}
