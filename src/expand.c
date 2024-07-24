
#include "../includes/../includes/minishell.h"

static void	expand_util(char *s, t_minishell *info, t_iterator *a, char *line)
{
	if (s[a->i] == '~' && (check_char(s[a->i - 1], " \t")
			|| s[a->i - 1] == '\0') && !a->single_quotes && !a->doubles_quotes)
		a->j += tilde(s, &line, info, a);
	else if (s[a->i] == '$' && !a->single_quotes)
		a->j += expand_env_v(s, &line, info, a);
	else if (s[a->i] == '<' && s[a->i + 1] == '<'
		&& !a->single_quotes && !a->doubles_quotes)
		no_expand_heredoc(s, line, a);
	else if (s[a->i] == '"' && !a->single_quotes)
		a->j += expand_doubles_quotes(a, line);
	else if (s[a->i] == '\'' && !a->doubles_quotes)
		a->j += expand_single_quotes(a, line);
	else
		line[a->j++] = s[a->i++];
}

char	*expand(char *s, t_minishell *info)
{
	char		*line;
	t_iterator	a;

	a = (t_iterator){0};
	line = NULL;
	line = ft_calloc(1, ft_strlen(s) + 1);
	if (line == NULL)
		exit_free_perror(NULL, ENV, info,
			BG_RED"memory allocation failed during parsing"RESET);
	while (s[a.i])
		expand_util(s, info, &a, line);
	return (line);
}
