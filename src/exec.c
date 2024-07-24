
#include "../includes/minishell.h"

int	is_builtin(t_cmd *c)
{
	if (c->cmd)
	{
		if ((ft_strcmp(c->cmd, "echo") == 0) || (ft_strcmp(c->cmd, "cd") == 0)
			|| (ft_strcmp(c->cmd, "pwd") == 0)
			|| (ft_strcmp(c->cmd, "export") == 0)
			|| (ft_strcmp(c->cmd, "unset") == 0)
			|| (ft_strcmp(c->cmd, "env") == 0)
			|| (ft_strcmp(c->cmd, "exit") == 0))
			return (1);
		return (0);
	}
	exit (130);
}

void	apply_exec_builtin(t_cmd *c, t_minishell *info)
{
	if (ft_strcmp(c->cmd, "echo") == 0)
		echo(c->arg, c->fd);
	if (ft_strcmp(c->cmd, "cd") == 0)
	{
		if (c->arg[1] != NULL)
			ft_putstr_fd("cd: too many arguments", 2);
		else
			cd(c->arg[0], info->env, info);
	}
	if (ft_strcmp(c->cmd, "pwd") == 0)
		pwd(c->fd);
	if (ft_strcmp(c->cmd, "export") == 0)
		info->env = our_export(c->arg, info->env, c->fd);
	if (ft_strcmp(c->cmd, "unset") == 0)
		info->env = unset(c->arg, info->env);
	if (ft_strcmp(c->cmd, "env") == 0)
		our_env(info->env, c->fd);
	if (ft_strcmp(c->cmd, "exit") == 0)
		our_exit(c, info);
}

void	exec_builtin(t_cmd *c, t_minishell *info, int fd, int pip[2])
{
	char	*path;

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
		apply_exec_builtin(c, info);
	if (is_builtin(c) == 0)
	{
		path = find_path(info->env, c->cmd);
		if (path != NULL)
			apply_exec_middle_bonus(fd, pip, info->env, c);
		if (c->outfile != NULL)
			close (c->fd);
		if (path == NULL)
			free_cmd(c, ENV, info);
	}
}
