
#include "../includes/minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	int	len1;
	int	len2;
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	join = ft_calloc(len1 + len2 + 1, 1);
	if (!join)
		return (NULL);
	ft_strcpy(join, s1);
	ft_strcpy(join + len1, s2);
	free(s1);
	return (join);
}

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
			if (envp[i][j] == '/')
				return (envp[i] + j);
		}
		i++;
	}
	return (NULL);
}

void	cd(char **arg, char **envp)
{
/*	char	*pwd;
	if (path == NULL)
	{
		chdir(get_home(envp, "HOME="));
		return ;
	}
	if (*path == '~')
	{
		if (!(pwd = get_env_variable("HOME=", envp)))
			return ; //free exit
		pwd = ft_strjoin_free(pwd, path + 1);
		chdir(pwd);
		free(pwd);
		return ;
	}
	pwd = getcwd(NULL, 0);
	pwd = ft_strjoin_free(pwd, "/");
	pwd = ft_strjoin_free(pwd, path);
	chdir(pwd);
	free(pwd);*/
	int		i;
	char	*pwd;
	
	i = 0;
	while (arg[i])
		i++;
	if (i > 1)
		printf("%s\n", "cd: too many arguments");
	if (arg[0] == NULL)
	{
		chdir(get_home(envp, "HOME="));
		return ;
	}
	if (*arg[0] == '~')
	{
		if (!(pwd = get_env_variable("HOME=", envp)))
			return ; //free exit
		pwd = ft_strjoin_free(pwd, arg[0] + 1);
		chdir(pwd);
		free(pwd);
		return ;
	}
	pwd = getcwd(NULL, 0);
	pwd = ft_strjoin_free(pwd, "/");
	pwd = ft_strjoin_free(pwd, arg[0]);
	chdir(pwd);
	free(pwd);
}
