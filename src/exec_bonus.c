
#include "../includes/minishell.h"


int	exec_midle(t_minishell *info, int fd, t_cmd *c)
{
	int		id;
	int		pip[2];

	if (c->next == NULL && c->previous_pipe != 1
		&& (ft_strcmp(c->cmd, "exit") == 0))
		our_exit(c, info);
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

void	exec(t_minishell *info, t_cmd *c)
{
	int	i;
	int	pipout;

	i = 0;
	pipout = 42;
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
