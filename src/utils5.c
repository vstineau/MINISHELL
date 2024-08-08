
#include "../includes/minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (s == NULL)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
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

void	free_and_close(int fd, int pip[2], t_cmd *c_first, int value)
{
	close_before(fd, pip, c_first);
	free_cmd(c_first, ENV, c_first->i);
	exit (value);
}

int	exec_first_case(t_cmd *c_first, t_cmd *c, int fd, int pip[2])
{
	c_first->close = 1;
	before_exec(c, c_first, fd, pip);
	return (fd);
}

void	wait_status(t_minishell *info, int status)
{
	int	exit_status;

	exit_status = 0;
	if (WIFEXITED(status))
	{
		exit_status = WEXITSTATUS(status);
		if (exit_status != 0)
			info->code_error = exit_status;
	}
}

char	*return_find_path(t_minishell *info, char *av, int error)
{
	if (error == 127)
	{
		info->code_error = 127;
		ft_putstr_fd(av, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (NULL);
	}
	if (error == 126)
	{
		info->code_error = 126;
		ft_putstr_fd(av, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (NULL);
	}
	return (NULL);
}
