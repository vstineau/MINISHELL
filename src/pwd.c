
#include "../includes/minishell.h"

void	pwd(int	fd)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	ft_putstr_fd(pwd, fd);
	ft_putstr_fd("\n", fd);
	free(pwd);
	if (fd != 1)
		close (fd);
}
