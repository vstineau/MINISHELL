
#include "../includes/minishell.h"

int	tilde(t_cmd *c, int i, t_minishell *info)
{
	if (!c->cmd)
	{
		c->cmd = get_env_variable("HOME=", info->env);
		if (!c->cmd)
		{
			free_cmd(c, ENV, info);
			perror(BG_RED"memory allocation failed during parsing"RESET);
			exit(1);
		}
	}
	else
	{
		c->arg[i] = get_env_variable("HOME=", info->env);
		if (!c->arg[i])
		{
			free_cmd(c, ENV, info);
			perror(BG_RED"memory allocation failed during parsing"RESET);
			exit(1);
		}
	}
	return (1);
}
