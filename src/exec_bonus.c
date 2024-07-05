
#include "../includes/minishell.h"

int	exec_first(char *av, char **env,  t_cmd *c)
{
	int		id;
	int		pip[2];
	char	*path;
	char	**cmd;
	int		infile;

	if (c->pipe == PIPE)
	{
		if (pipe(pip) == -1)
			perror("");
	}
	id = fork();
	if (id == -1)
		perror("");
	if (id == 0)
	{
		if (c->infile)
		{
			infile = check_infile(c->infile);
			if (infile == -1)
				exit_close(pip);
			close(infile);
		}
		path = find_path(env, av);
		cmd = find_cmd(av);
		if (path != NULL && cmd != NULL)
			apply_exec_first_bns(av, env, c->infile, pip, c);
		free_alls(path, cmd);
		exit_close(pip);
	}
	return (pip[0]);
}

int	exec_midle(char *av, char **env, int fd, t_cmd *c)
{
	char	*path;
	char	**cmd;
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
		cmd = find_cmd(av);
		if (path != NULL && cmd != NULL)
			apply_exec_middle_bonus(fd, pip, env, av, c);
		free_alls(path, cmd);
		close (fd);
		close (pip[1]);
		exit (-1);
	}
	close(pip[1]);
	close(fd);
	return (pip[0]);
}

void	exec_last(char *av, char **env, char *file, int fd, t_cmd *c)
{
	int		id;
	char	*path;
	char	**cmd;
	int		outfile;

	outfile = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (outfile == -1)
		perror("");
	id = fork();
	if (id == -1)
		perror("");
	if (id == 0)
	{
		path = find_path(env, av);
		cmd = find_cmd(av);
		if (path != NULL && cmd != NULL)
			apply_exec_last_bns(av, env, outfile, fd, c);
		close (outfile);
		free_split(cmd);
		free(path);
		close (fd);
		exit (-1);
	}
	close (fd);
	close (outfile);
}

void	exec(char **env, t_cmd *c)
{
	int	i;
	int	pipout;

	i = 2;
	pipout = 42;
	if (c->cmd)
	{
		pipout = exec_first(c->cmd, env, c);
	}
	//while (i < ac - 1)
	//{
	//	if (i == 2)
	//		pipout = exec_first(av[2], env, av[1], c);
	//	else if (i == ac - 2)
	//		exec_last(av[ac - 2], env, av[ac - 1], pipout, c);
	//	else if (i > 2 && i < ac - 2)
	//		pipout = exec_midle(av[i], env, pipout, c);
	//	i++;
	//}

	while (wait(NULL) > 0)
		;
	close (pipout);
	
}
