
#include "../includes/minishell.h"
#include <errno.h>

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (s == NULL)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		if (write(fd, &s[i], 1) != 1)
			errno = ENOSPC;
		i++;
	}
}

void	ft_sort_strings(int num, char **s)
{
	int		i;
	int		j;
	char	*temp;

	i = 1;
	j = 0;
	while (i < num)
	{
		j = i;
		while (j > 0 && ft_strcmp(s[j - 1], s[j]) > 0)
		{
			temp = s[j - 1];
			s[j - 1] = s[j];
			s[j] = temp;
			j--;
		}
		i++;
	}
}

void	set_error_code(t_cmd *c, int code)
{
	c->i->code_error = code;
	c->error = 1;
}

static void	check_unwanted_char_arg(t_cmd *c, t_cmd *cfirst)
{
	int	i;
	int	j;

	i = 0;
	while (c->arg[i])
	{
		j = 0;
		while (c->arg[i][j])
		{
			if (!check_char(c->arg[i][j], "&;()"))
				break ;
			j++;
		}
		if (!c->arg[i][j])
			set_error_code(cfirst, 2);
		i++;
	}
}

void	check_unwanted_char_cmd(t_cmd *c)
{
	t_cmd	*current;
	int		i;

	current = c;
	while (current)
	{
		i = 0;
		while (current->cmd[i])
		{
			if (!check_char(current->cmd[i], "&;()"))
				break ;
			i++;
		}
		if (!current->cmd[i])
			set_error_code(c, 2);
		check_unwanted_char_arg(current, c);
		current = current->next;
		while (current && current->pipe == PIPE)
			current = current->next;
	}
}
