
#include "../includes/minishell.h"

int	is_builtin(t_cmd *c)
{
	if ((ft_strcmp(c->cmd, "echo") == 0) || (ft_strcmp(c->cmd, "cd") == 0)
		|| (ft_strcmp(c->cmd, "pwd") == 0) || (ft_strcmp(c->cmd, "export") == 0)
		|| (ft_strcmp(c->cmd, "unset") == 0) || (ft_strcmp(c->cmd, "env") == 0)
		|| (ft_strcmp(c->cmd, "exit") == 0))
		return (1);	
	return (0);
}

void	exec_builtin(t_cmd *c, t_minishell *info)
{
	int	i;
	
	i = is_builtin(c);
	if (ft_strcmp(c->cmd, "echo") == 0) 
		echo(c->arg, c->fd);
	if (ft_strcmp(c->cmd, "cd") == 0)
		cd(c->path, info->env);
	if (ft_strcmp(c->cmd, "pwd") == 0)
		pwd();
	if (ft_strcmp(c->cmd, "export") == 0)
		our_export(c->arg, info->env);
	if (ft_strcmp(c->cmd, "unset") == 0)
		unset(c->arg, info->env);
	if (ft_strcmp(c->cmd, "env") == 0)
		our_env(info->env);
	if (ft_strcmp(c->cmd, "exit") == 0)
		our_exit(c, info);
	if (i == 0)
		i = 0;
		//exec(		
}
