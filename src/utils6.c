
#include "../includes/minishell.h"

int	check_error(t_cmd *c)
{
	t_cmd	*current;

	current = c;
	while (current)
	{
		if (current->error)
			return (1);
		current = current->next;
	}
	return (0);
}
