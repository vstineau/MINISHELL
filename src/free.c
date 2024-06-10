
#include "../includes/minishell.h"

void	free_Cmd(t_cmd *cmd)
{
	while (cmd)
	{
		free(cmd->cmd);
		free(cmd->infile);
		free(cmd->outfile);
		free(cmd->heredoc);
		free_split(cmd->arg);
		cmd = cmd->next;
	}
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	 free(split[i++]);
	free(split);
}
