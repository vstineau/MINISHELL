
#include "../includes/minishell.h"

void	apply_exec_first_bns(char *av, char **env, char *file, int pip[2], t_cmd *c)
{
	char	*path;
	char	**cmd;
	int		infile;

	infile = 0;
	if (file != NULL) 
	{
		infile = open(file, O_RDONLY);
		if (infile == -1)
			perror("");
	}
	path = find_path(env, av);
	cmd = find_cmd(av);
	if (infile) 
	{
		if (dup2(infile, STDIN_FILENO) == -1)
			perror("");
	}
	
	if (c->outfile) 
	{
		if (dup2(pip[1], STDOUT_FILENO) == -1)
			perror("");
	}
	ft_close(pip, infile);
	if (execve(path, cmd, env) == -1)
	{
		free (path);
		free_split(cmd);
		exit(-1);
	}
	free (path);
	free_split(cmd);
}

void	apply_exec_middle_bonus(int fd, int pip[2], char **env, char *av, t_cmd *c)
{
	char	*path;
	char	**cmd;

	if (c->infile) 
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			perror("");
	}
	if (c->outfile) 
	{
		if (dup2(pip[1], STDOUT_FILENO) == -1)
		perror("");
	}
	close(fd);
	close(pip[1]);
	path = find_path(env, av);
	cmd = find_cmd(av);
	if (execve(path, cmd, env) == -1)
	{
		close (pip[0]);
		free (path);
		free_split(cmd);
		exit(-1);
	}
	free_split(cmd);
	free(path);
}

void	apply_exec_last_bns(char *av, char **env, int outfile, int fd, t_cmd *c)
{
	char	*path;
	char	**cmd;

	path = find_path(env, av);
	cmd = find_cmd(av);
	if (c->infile) 
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			perror("");
	}
	if (c->outfile)
	{
		if (dup2(outfile, STDOUT_FILENO) == -1)
			perror("");
	}
	close (fd);
	close (outfile);
	if (execve(path, cmd, env) == -1)
	{
		free (path);
		free_split(cmd);
		exit(-1);
	}
	free (path);
	free_split(cmd);
}
