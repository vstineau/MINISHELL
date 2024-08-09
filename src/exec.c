/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstineau <vstineau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:54:05 by vstineau          #+#    #+#             */
/*   Updated: 2024/08/09 14:57:48 by vstineau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <unistd.h>

int	is_builtin(t_cmd *c)
{
	if (c->cmd)
	{
		if ((ft_strcmp(c->cmd, "echo") == 0) || (ft_strcmp(c->cmd, "cd") == 0)
			|| (ft_strcmp(c->cmd, "pwd") == 0)
			|| (ft_strcmp(c->cmd, "export") == 0)
			|| (ft_strcmp(c->cmd, "unset") == 0)
			|| (ft_strcmp(c->cmd, "env") == 0)
			|| (ft_strcmp(c->cmd, "exit") == 0)
			|| (ft_strcmp(c->cmd, ":") == 0)
			|| (ft_strcmp(c->cmd, "!") == 0)
			|| (ft_strcmp(c->cmd, ".") == 0)
			|| (ft_strcmp(c->cmd, "#") == 0))
			return (1);
		return (0);
	}
	return (0);
}

void	exit_code_weird(t_cmd *c)
{
	if (ft_strcmp(c->cmd, ":") == 0)
		c->i->code_error = 0;
	if (ft_strcmp(c->cmd, "!") == 0)
		c->i->code_error = 1;
	if (ft_strcmp(c->cmd, "#") == 0)
		c->i->code_error = 0;
	if (ft_strcmp(c->cmd, ".") == 0)
	{
		ft_putstr_fd(".: filename argument required\n", 2);
		c->i->code_error = 2;
	}
}

void	exec_builtin(t_cmd *c, t_cmd *c_first, int pip[2], int fd)
{
	if ((ft_strcmp(c->cmd, ":") == 0) || (ft_strcmp(c->cmd, "!") == 0)
		|| (ft_strcmp(c->cmd, "#") == 0) || (ft_strcmp(c->cmd, ".") == 0))
		exit_code_weird(c);
	if (ft_strcmp(c->cmd, "echo") == 0)
		echo(c->arg, c->fd);
	if (ft_strcmp(c->cmd, "cd") == 0)
	{
		if (c->arg[1] != NULL)
		{
			c->i->code_error = 1;
			ft_putstr_fd("cd: too many arguments\n", 2);
		}
		else
			cd(c->arg[0], c_first->i->env, c->i);
	}
	if (ft_strcmp(c->cmd, "pwd") == 0)
		pwd(c->fd, c);
	if (ft_strcmp(c->cmd, "export") == 0)
		c_first->i->env = our_export(c->arg, c_first->i->env, c->fd, c);
	if (ft_strcmp(c->cmd, "unset") == 0)
		c_first->i->env = unset(c->arg, c_first->i->env, c);
	if (ft_strcmp(c->cmd, "env") == 0)
		our_env(c_first->i->env, c->fd, c);
	if (ft_strcmp(c->cmd, "exit") == 0)
		our_exit(c, c_first, pip, fd);
}

void	apply_exec_path(t_cmd *c, t_cmd *c_first, int fd, int pip[2])
{
	if (c->path != NULL)
		apply_exec_middle(fd, pip, c_first, c);
	if (c->outfile != NULL)
		close (c->fd);
}

void	before_exec(t_cmd *c, t_cmd *c_first, int fd, int pip[2])
{
	c->fd = 1;
	if (c->outfile != NULL)
		c->fd = open(c->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
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
	if (is_builtin(c) == 1)
	{
		c->i->code_error = 0;
		exec_builtin(c, c_first, pip, fd);
	}
	if (is_builtin(c) == 0)
		apply_exec_path(c, c_first, fd, pip);
}
