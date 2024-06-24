
#include "../includes/minishell.h"

void	free_cmd(t_cmd *cmd, bool env, t_minishell *info)
{
	t_cmd *temp;

	if (env)
		free_split(info->env);
	while (cmd)
	{
		temp = cmd;
		if (cmd->cmd)
			free(cmd->cmd);
		if (cmd->infile)
			free(cmd->infile);
		if (cmd->outfile)
			free(cmd->outfile);
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
