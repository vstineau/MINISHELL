
#include "../includes/minishell.h"

int	exec_first(char *av, char **env, char *file)
{
	int		id;
	int		pip[2];
	char	*path;
	char	**cmd;
	int		infile;

	if (pipe(pip) == -1)
		perror("");
	id = fork();
	if (id == -1)
		perror("");
	if (id == 0)
	{
		infile = check_infile(file);
		if (infile == -1)
			exit_close(pip);
		close(infile);
		path = find_path(env, av);
		cmd = find_cmd(av);
		if (path != NULL && cmd != NULL)
			apply_exec_first_bns(av, env, file, pip);
		free_all(path, cmd);
		exit_close(pip);
	}
	return (close(pip[1]), pip[0]);
}

int	exec_midle(char *av, char **env, int fd)
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
			apply_exec_middle_bonus(fd, pip, env, av);
		free_all(path, cmd);
		close (fd);
		close (pip[1]);
		exit (-1);
	}
	close(pip[1]);
	close(fd);
	return (pip[0]);
}

void	exec_last(char *av, char **env, char *file, int fd)
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
			apply_exec_last_bns(av, env, outfile, fd);
		close (outfile);
		free_split(cmd);
		free(path);
		close (fd);
		exit (-1);
	}
	close (fd);
	close (outfile);
}

int	main(int ac, char **av, char **env)
{
	int	i;
	int	pipout;

	i = 2;
	pipout = 42;
	while (i < ac - 1)
	{
		if (i == 2)
			pipout = exec_first(av[2], env, av[1]);
		else if (i == ac - 2)
			exec_last(av[ac - 2], env, av[ac - 1], pipout);
		else if (i > 2 && i < ac - 2)
			pipout = exec_midle(av[i], env, pipout);
		i++;
	}
	while (wait(NULL) > 0)
		;
	close (pipout);
}
