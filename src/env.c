
#include "../includes/minishell.h"

void	our_env(char **env, int fd)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i] != NULL && ft_strchr(env[i], '=') != NULL)
		{
			ft_putstr_fd(env[i], fd);
			ft_putstr_fd("\n", fd);
		}
		i++;
	}
	if (fd != 1)
		close (fd);
}
