
#include "../includes/minishell.h"

int	is_blank(char *s)
{
	int	i;

	if (!s)
		return (1);
	i = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

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

int	check_before_exec(char *cmd, t_cmd *c)
{
	if ((!is_blank(cmd) && !check_error(c)
			&& g_signal_received != SIGINT) || !is_blank(c->outfile))
		return (1);
	else
		return (0);
}
