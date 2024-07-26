
#include "../includes/minishell.h"

int	exec_midle(t_minishell *info, int fd, t_cmd *c)
{
	int		id;
	int		pip[2];

	if (c->next == NULL && c->previous_pipe != 1 && (is_builtin(c) == 1))
	{
		exec_builtin(c, info, fd, pip);
		return (fd);
	}
	if (pipe(pip) == -1)
		exit(EXIT_FAILURE);
	id = fork();
	if (id == -1)
		perror("");
	if (id == 0)
	{
		close(pip[0]);
		exec_builtin(c, info, fd, pip);
		close (fd);
		close (pip[1]);
		exit (-1);
	}
	close(pip[1]);
	close(fd);
	return (pip[0]);
}

int	init_sigquit(t_minishell *info)
{
	sigemptyset(&info->sig.sa_mask);
	info->sig.sa_sigaction = handle_sigquit;
	if (sigaction(SIGQUIT, &info->sig, NULL) == -1)
		return (0);
	return (1);
}

int	check_dobble_pipe(t_cmd *test, int pipout)
{
	while (test)
	{
		if (test->pipe == PIPE)
			test->next->previous_pipe = 1;
		if (test->previous_pipe == 1 && test->pipe == 0
			&& !test->cmd && !test->infile && !test->outfile)
		{
			close (pipout);
			return (1);
		}
		test = test->next;
	}
	return (0);
}

void	exec(t_minishell *info, t_cmd *c)
{
	int		i;
	int		pipout;
	t_cmd	*test;

	test = c;
	i = 0;
	pipout = 42;
	if (init_sigquit(info) == 0)
		exit_free_perror(c, ENV, info, "");
	if (check_dobble_pipe(test, pipout) == 1)
		return (ft_putstr_fd("syntax error near unexpected token `|'\n", 2));
	{
		while (c)
		{
			if (c->cmd)
				pipout = exec_midle(info, pipout, c);
			if (c->pipe == PIPE)
				c->next->previous_pipe = 1;
			c = c->next;
		}
		while (wait(NULL) > 0)
			;
		close (pipout);
	}
}
