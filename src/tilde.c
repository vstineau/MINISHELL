
#include "../includes/minishell.h"

int	tilde(char *s, char **line, t_minishell *info, t_iterator *a)
{
	int	len_home;
	int	len_line;
	char *home;

	if (check_char(*(s + 1), " \t"))
	{
		ft_memcpy(*line + a->j, " ", 1);
		return (1);
	}
	len_line = ft_strlen(s);
	home = get_env_variable("HOME=", info->env);
	if (!home)
	{
		ft_memcpy(*line + a->j, s + a->i, 1);
		return (1);
	}
	else
	{
		len_home = ft_strlen(home);
		*line = ft_realloc(*line, len_line, len_home + len_line + 1);
		if (*line == NULL)
		{
			free_cmd(NULL, ENV, info);
			perror(BG_RED"memory allocation failed during parsing"RESET);
			exit(1);
		}
		ft_memcpy(*line + a->i, home, len_home);
		a->i += 1;
	}
	free(home);
	return (len_home);
}
