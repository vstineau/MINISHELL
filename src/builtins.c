
#include "../includes/minishell.h"

int	is_builtin(char **cmd)
{
	if ((ft_strcmp(cmd[0], "echo") == 0) || (ft_strcmp(cmd[0], "cd") == 0)
		|| (ft_strcmp(cmd[0], "pwd") == 0) || (ft_strcmp(cmd[0], "export") == 0)
		|| (ft_strcmp(cmd[0], "unset") == 0) || (ft_strcmp(cmd[0], "env") == 0)
		|| (ft_strcmp(cmd[0], "exit") == 0))
		return (1);	
	return (0);
}

char *exec_builtin(char **cmd, int infile, int outfile)
{
	if (ft_strcmp(cmd[0], "echo") == 0) 
	if (ft_strcmp(cmd[0], "cd") == 0)
	if (ft_strcmp(cmd[0], "pwd") == 0) 
	if (ft_strcmp(cmd[0], "export") == 0)
	if (ft_strcmp(cmd[0], "unset") == 0) 
	if (ft_strcmp(cmd[0], "env") == 0)
	if (ft_strcmp(cmd[0], "exit") == 0)

