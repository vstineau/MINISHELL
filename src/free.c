
#include "../includes/minishell.h"

void	free_cmd(t_cmd *cmd)
{
	t_cmd *temp;

	while (cmd)
	{
		temp = cmd;
		free(cmd->cmd);
		free(cmd->infile);
		free(cmd->outfile);
		free_split(cmd->arg);
		cmd = cmd->next;
		free(temp);
	}
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
