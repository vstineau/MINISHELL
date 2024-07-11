
#include "../includes/minishell.h"


int	exec_midle(char *av, char **env, int fd, t_cmd *c)
{
	char	*path;
//	char	**cmd;
	int		id;
	int		pip[2];

	if (pipe(pip) == -1)
		exit(EXIT_FAILURE);
	id = fork();
	if (id == -1)
		perror("");
	if (id == 0)
	{
		close(pip[0]);
		path = find_path(env, av);
		//cmd = find_cmd(av);
		if (path != NULL)
			apply_exec_middle_bonus(fd, pip, env, c);
		close (fd);
		close (pip[1]);
		exit (-1);
	}
	close(pip[1]);
	close(fd);
	return (pip[0]);
}

void	exec(char **env, t_cmd *c)
{
	int	i;
	int	pipout;

	i = 0;
	pipout = 42;
	while (c)
	{
		if (c->cmd)
			pipout = exec_midle(c->cmd, env, pipout, c);
		if (c->pipe == PIPE)
			c->next->previous_pipe = 1;
		c = c->next;
	}
	while (wait(NULL) > 0)
		;
	close (pipout);
	
}
