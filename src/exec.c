
#include "../includes/minishell.h"

int	is_builtin(t_cmd *c)
{
	if (c->cmd)
	{	if ((ft_strcmp(c->cmd, "echo") == 0) || (ft_strcmp(c->cmd, "cd") == 0)
		|| (ft_strcmp(c->cmd, "pwd") == 0) || (ft_strcmp(c->cmd, "export") == 0)
		|| (ft_strcmp(c->cmd, "unset") == 0) || (ft_strcmp(c->cmd, "env") == 0)
		|| (ft_strcmp(c->cmd, "exit") == 0))
			return (1);	
		return (0);
	}
	exit (130);
}

void	exec_builtin(t_cmd *c, t_minishell *info)
{
	int	i;
	c->fd = 1;
	if (c->outfile != NULL)
		c->fd = open(c->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	i = is_builtin(c);
	if (ft_strcmp(c->cmd, "echo") == 0) 
		echo(c->arg, c->fd);
	else if (ft_strcmp(c->cmd, "cd") == 0)
		cd(c->arg, info->env);
	else if (ft_strcmp(c->cmd, "pwd") == 0)
		pwd(c->fd);
	else if (ft_strcmp(c->cmd, "export") == 0)
		info->env = our_export(c->arg, info->env, c->fd);
	else if (ft_strcmp(c->cmd, "unset") == 0)
		info->env = unset(c->arg, info->env);
	else if (ft_strcmp(c->cmd, "env") == 0)
		our_env(info->env, c->fd);
	else if (ft_strcmp(c->cmd, "exit") == 0)
		our_exit(c, info);
	else if (i == 0)
		exec(info->env, c);
}
