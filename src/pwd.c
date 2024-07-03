
#include "../includes/minishell.h"

void	pwd(int	fd)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	ft_putstr_fd(pwd, fd);
	free(pwd);
}
