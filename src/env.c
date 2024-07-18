
#include "../includes/minishell.h"

void	our_env(char **env, int fd)
{
	int	i;
	char *test;
	
	i = 0;
	while (env[i])
	{
		test = ft_strchr(env[i], '=');
		if (env[i] != NULL && test != NULL && test[1] != '\0')
		{
			ft_putstr_fd(env[i], fd);
			ft_putstr_fd("\n", fd);
		}
		i++;
	}
	if (fd != 1)
		close (fd);
}
