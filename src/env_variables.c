
#include "../includes/minishell.h"

//static char *get_env_variable(char *var, char **envp)
//{
//	int	i;
//	int	j;
//	char	*h;
//
//	i = 0;
//	h = NULL;
//	while(envp[i])
//	{
//	 j = 0;
//		if (envp[i][j] == var[j])
//		{
//			while(envp[i][j] == var[j])
//				j++;
//			if (envp[i][j] && envp[i][j] != '=')
//			{
//				h = ft_calloc(ft_strlen(envp[i] + j) + 1, 1);
//				if (!h)
//					return (NULL);
//				ft_strcpy(h, envp[i] + j);
//				return (h);
//			}
//		}
//		i++;
//	}
//	free(h);
//	return (NULL);
//}
//
//void	env_variables(char *s, char **envp, t_cmd *c)
//{
//	(void)s;
//	(void)c;
//	(void)envp;
//}
