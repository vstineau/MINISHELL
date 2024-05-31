
#include "../includes/minishell.h"

t_cmd	*new_cmd(char *content)
{
	char	**temp;
	t_cmd	*cmd;
	int	i;

	i = 1;
	cmd = ft_calloc(1, sizeof(*cmd));
	if (!cmd)
		return (NULL);
	temp = ft_split(content, ' ');
	ft_strcpy(cmd->cmd, temp[0]);
	while (temp[i])
	{
		ft_strcpy(cmd->arg[i - 1], temp[i]);
		i++;
	}
	free_split(temp);
	return (cmd);
}

t_cmd	*parse(char *line)
{
	t_cmd	*cmd;
	char **pipes;

	pipes = ft_split(line, '|');
	cmd = new_cmd(pipes[0]);
	free(line);
	
	return (cmd);
}
