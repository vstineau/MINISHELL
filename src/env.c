
#include "../includes/minishell.h"

void	my_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i] != NULL)
		{
			printf("%s\n", env[i]);
		}
		i++;
	}
}
