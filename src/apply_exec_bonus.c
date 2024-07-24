
#include "../includes/minishell.h"
#include <unistd.h>

void	apply_exec(t_cmd *c, char **env, int pip[2])
{
	char	**cmd;
	char	*path;
	int		i;

	i = 1;
	path = find_path(env, c->cmd);
	cmd = ft_calloc(sizeof(char **), env_size(c->arg) + 2);
	cmd[0] = c->cmd;
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
}

void	close_before(int fd, int pip[2], t_cmd *c)
{
	(void) c;
	if (c->outfile != NULL)
		close (c->fd);
	close (fd);
	close(pip[1]);
}

void	apply_exec_middle_bonus(int fd, int pip[2], char **env, t_cmd *c)
{
	int		infile;

	if (c->infile)
	{
		infile = open(c->infile, O_RDONLY);
		if (infile == -1)
			perror("");
		if (dup2(infile, STDIN_FILENO) == -1)
			perror("");
		close (infile);
	}
	if (c->previous_pipe == 1)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			perror("");
	}
	if (c->next && c->next->pipe == PIPE)
	{
		if (dup2(pip[1], STDOUT_FILENO) == -1)
			perror("");
	}
	close_before(fd, pip, c);
	apply_exec(c, env, pip);
}
