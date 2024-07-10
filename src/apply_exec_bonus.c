
#include "../includes/minishell.h"
#include <unistd.h>

void	apply_exec_first_bns(char *av, char **env, int pip[2], t_cmd *c)
{
	char	*path;
	char	**cmd;
	int		infile;

	infile = 0;
	if (c->infile != NULL) 
	{
		infile = open(c->infile, O_RDONLY);
		if (infile == -1)
			perror("");
	}
 	if (c->infile) 
	{
		if (dup2(infile, STDIN_FILENO) == -1)
			perror("");
	}
	if (c->outfile) 
	{
		if (dup2(pip[1], STDOUT_FILENO) == -1)
			perror("");
	}
	path = find_path(env, av);
	cmd = ft_calloc(sizeof(char **), env_size(c->arg) + 2);
	cmd[0] = av;
	int i = 1;
	while (c->arg[i - 1])
	{
		cmd[i] = ft_calloc(sizeof(char *), ft_strlen(c->arg[i - 1]) + 1);
		ft_memcpy(cmd[i], c->arg[i - 1], ft_strlen(c->arg[i - 1]));
		i++;
	}
	//ft_close(pip, infile);
	if (execve(path, cmd, env) == -1)
	{
		free (path);
		free_split(cmd);
		exit(-1);
	}
	free_split(cmd);
	//close(pip[0]);
	//close(pip[1]);
	//close(pip[2]);
	free (path);

}

void	apply_exec_middle_bonus(int fd, int pip[2], char **env, char *av, t_cmd *c)
{
	char	*path;
	char	**cmd;

	if (c->next && c->next->pipe == PIPE)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			perror("");
	}
	if (c->next && c->next->pipe == PIPE)
	{
		if (dup2(pip[1], STDOUT_FILENO) == -1)
		perror("");
	}
	close(fd);
	close(pip[1]);
	path = find_path(env, av);
	cmd = ft_calloc(sizeof(char **), env_size(c->arg) + 2);
	cmd[0] = av;
	int i = 1;
	while (c->arg[i - 1])
	{
		cmd[i] = ft_calloc(sizeof(char *), ft_strlen(c->arg[i - 1]) + 1);
		ft_memcpy(cmd[i], c->arg[i - 1], ft_strlen(c->arg[i - 1]));
		i++;
	}
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
