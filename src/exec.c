
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
	exit (130);
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

void	apply_exec_builtin(t_cmd *c, t_minishell *info)
{
	if ((ft_strcmp(c->cmd, ":") == 0) || (ft_strcmp(c->cmd, "!") == 0)
		|| (ft_strcmp(c->cmd, "#") == 0) || (ft_strcmp(c->cmd, ".") == 0))
		exit_code_weird(c);
	if (ft_strcmp(c->cmd, "echo") == 0)
		echo(c->arg, c->fd);
	if (ft_strcmp(c->cmd, "cd") == 0)
	{
		if (c->arg[1] != NULL)
			ft_putstr_fd("cd: too many arguments\n", 2);
		else
			cd(c->arg[0], info->env, info);
	}
	if (ft_strcmp(c->cmd, "pwd") == 0)
		pwd(c->fd);
	if (ft_strcmp(c->cmd, "export") == 0)
		info->env = our_export(c->arg, info->env, c->fd, c);
	if (ft_strcmp(c->cmd, "unset") == 0)
		info->env = unset(c->arg, info->env);
	if (ft_strcmp(c->cmd, "env") == 0)
		our_env(info->env, c->fd, c);
	if (ft_strcmp(c->cmd, "exit") == 0)
		our_exit(c, info);
}

void	apply_exec_path(t_cmd *c, t_minishell *info, int fd, int pip[2])
{
	if (c->path != NULL)
	{
		apply_exec_middle_bonus(fd, pip, info->env, c);
	}
	if (c->outfile != NULL)
		close (c->fd);
	if (c->path == NULL)
	{
		close_before(fd, pip, c);
		free_cmd(c, ENV, info);
		exit (info->code_error);
	}
}

void	exec_builtin(t_cmd *c, t_minishell *info, int fd, int pip[2])
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
		info->code_error = 0;
		apply_exec_builtin(c, info);
	}
	if (is_builtin(c) == 0)
		apply_exec_path(c, info, fd, pip);
}
