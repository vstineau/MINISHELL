/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_exec_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstineau <vstineau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:53:20 by vstineau          #+#    #+#             */
/*   Updated: 2024/08/09 14:58:20 by vstineau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <unistd.h>
#include <errno.h>

void	apply_exec(t_cmd *c, char **env, int pip[2], t_cmd *c_first)
{
	char	**cmd;
	int		i;

	i = 1;
	cmd = ft_calloc(sizeof(char **), env_size(c->arg) + 2);
	cmd[0] = c->cmd;
	while (c->arg[i - 1])
	{
		cmd[i] = ft_calloc(sizeof(char *), ft_strlen(c->arg[i - 1]) + 1);
		ft_memcpy(cmd[i], c->arg[i - 1], ft_strlen(c->arg[i - 1]));
		i++;
	}
	if (c->outfile != NULL)
		close (c->fd);
	if (execve(c->path, cmd, env) == -1)
	{
		printf("command = %s \n", c->path);
		errno = EISDIR;
		perror(c->path);
		close (pip[0]);
		free(cmd);
		free_cmd(c_first, ENV, c->i);
		exit(126);
	}
	free_split(cmd);
}

void	close_before(int fd, int pip[2], t_cmd *c)
{
	if (c->close == 0)
	{
		close (fd);
		close(pip[1]);
	}
}

void	dup_infile(t_cmd *c)
{
	int		infile;

	infile = open(c->infile, O_RDONLY);
	if (infile == -1)
		perror("");
	if (dup2(infile, STDIN_FILENO) == -1)
		perror("");
	close (infile);
}

void	apply_exec_middle(int fd, int pip[2], t_cmd *c_first, t_cmd *c)
{
	if (c->infile)
	{
		dup_infile(c);
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
	if (c->outfile)
	{
		if (dup2(c->fd, STDOUT_FILENO) == -1)
			perror("");
	}
	close_before(fd, pip, c_first);
	apply_exec(c, c->i->env, pip, c_first);
}
