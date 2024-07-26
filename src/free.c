
#include "../includes/minishell.h"

void	free_cmd(t_cmd *cmd, bool env, t_minishell *info)
{
	t_cmd	*temp;

	if (env)
		free_split(info->env);
	while (cmd)
	{
		temp = cmd;
		if (cmd->fd_h != -1 && cmd->fd_h != 0)
			close(cmd->fd_h);
		if (cmd->cmd)
			free(cmd->cmd);
		if (cmd->infile && cmd->redirect == NO_HEREDOC)
			free(cmd->infile);
		if (cmd->outfile)
			free(cmd->outfile);
		if (cmd->arg)
			free_split(cmd->arg);
		cmd = cmd->next;
		free(temp);
	}
	unlink("heredoc");
	cmd = NULL;
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	exit_free_perror(t_cmd *c, bool env, t_minishell *info, char *error)
{
	if (error)
		perror(error);
	free_cmd(c, env, info);
	exit(1);
}
