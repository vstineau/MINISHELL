
#include "../includes/minishell.h"

char *get_home(char **envp, char *home)
{
	int	i;
	int	j;

	 i = 0;
	while(envp[i])
	{
	 j = 0;
		if (envp[i][j] == home[j])
		{
			while(envp[i][j] == home[j])
				j++;
			if (home[j] == '\0')
				return (envp[i] + j);
		}
		i++;
	}
	return (NULL);
}


void	cd(char *path, char **envp)
{
	if (path == NULL)
		chdir(get_home(envp, "HOME="));
	else
		chdir(path);
}
