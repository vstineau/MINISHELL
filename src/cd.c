
#include "../includes/minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	int		len1;
	int		len2;
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

char	*get_home(char **envp, char *home)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		if (envp[i][j] == home[j])
		{
			while (envp[i][j] == home[j])
				j++;
			if (envp[i][j] == '/')
				return (envp[i] + j);
		}
		i++;
	}
	return (NULL);
}

void	cd(char *path, char **envp, t_minishell *info)
{
	char	*pwd;

	if (path == NULL)
	{
		chdir(get_home(envp, "HOME="));
		return ;
	}
	if (*path == '~')
	{
		pwd = get_env_variable("HOME=", envp, NULL, info);
		pwd = ft_strjoin_free(pwd, path + 1);
		chdir(pwd);
		free(pwd);
		return ;
	}
	pwd = getcwd(NULL, 0);
	pwd = ft_strjoin_free(pwd, "/");
	pwd = ft_strjoin_free(pwd, path);
	chdir(pwd);
	free(pwd);
}
