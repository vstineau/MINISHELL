
#include "../includes/minishell.h"

int	check_error(t_cmd *c)
{
	t_cmd	*current;

	current = c;
	while (current)
	{
		if (current->error == 1)
			return (1);
		if (current->error == 2)
			return (2);
		current = current->next;
	}
	return (0);
}
