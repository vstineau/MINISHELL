
#include "../includes/minishell.h"

static int	tilde_util(char *s, char **line, t_iterator *a)
{
	ft_memcpy(*line + a->j, s + a->i, 1);
	return (1);
}

int	tilde(char *s, char **line, t_minishell *info, t_iterator *a)
{
	int		len_home;
	int		len_line;
	char	*home;

	if (check_char(*(s + 1), " \t"))
	{
		ft_memcpy(*line + a->j, " ", 1);
		return (1);
	}
	len_line = ft_strlen(s);
	home = get_env_variable("HOME=", info->env, NULL, info);
	if (!home)
		return (tilde_util(s, line, a));
	else
	{
		len_home = ft_strlen(home);
		*line = ft_realloc(*line, len_line, len_home + len_line + 1);
		if (*line == NULL)
			exit_free_perror(NULL, ENV, info,
				BG_RED"memory allocation failed during parsing"RESET);
		ft_memcpy(*line + a->i, home, len_home);
		a->i += 1;
	}
	free(home);
	return (len_home);
}
