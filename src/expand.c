/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstineau <vstineau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:54:29 by vstineau          #+#    #+#             */
/*   Updated: 2024/08/09 14:57:48 by vstineau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/../includes/minishell.h"

static int	is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

// a $42EXAMPLE line should be extand as 2EXAMPLE
static int	expand_dols_number(char *s, char **line, t_iterator *a)
{
	int		j;
	int		len_line;

	len_line = ft_strlen(*line);
	if (len_line < ft_strlen(s))
		len_line = ft_strlen(s);
	j = 2 + a->i;
	a->i += j - a->i;
	return (0);
}

static void	expand_util(char *s, t_minishell *info, t_iterator *a, char **line)
{
	if (s[a->i] == '~' && (check_char(s[a->i - 1], " \t")
			|| s[a->i - 1] == '\0') && !a->single_quotes && !a->doubles_quotes)
		a->j += tilde(s, line, info, a);
	else if (s[a->i] == '$' && is_num(s[a->i + 1]) && !a->single_quotes)
		a->j += expand_dols_number(s, line, a);
	else if (s[a->i] == '$' && s[a->i + 1] == '?' && !a->single_quotes)
			a->j += expand_dols_qmark(s, line, info, a);
	else if (s[a->i] == '$' && !a->single_quotes)
	{
		a->j += expand_env_v(s, line, info, a);
		if (a->dols_end)
			a->j += get_dols(line, a, info);
	}
	else if (s[a->i] == '<' && s[a->i + 1] == '<'
		&& !a->single_quotes && !a->doubles_quotes)
		no_expand_heredoc(s, *line, a);
	else if (s[a->i] == '"' && !a->single_quotes)
		a->j += expand_doubles_quotes(a, *line);
	else if (s[a->i] == '\'' && !a->doubles_quotes)
		a->j += expand_single_quotes(a, *line);
	else if (s[a->i])
		(*line)[a->j++] = s[a->i++];
}

//expand all of the '~' and the $*** variables depending on the "" '' and <<
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
		expand_util(s, info, &a, &line);
	return (line);
}

// change $? to a itoa of lasr error code
int	expand_dols_qmark(char *s, char **line, t_minishell *info, t_iterator *a)
{
	int		j;
	char	*code_error;
	int		len_line;
	int		len_code_error;

	len_line = ft_strlen(*line);
	if (len_line < ft_strlen(s))
		len_line = ft_strlen(s);
	j = 2 + a->i;
	code_error = NULL;
	code_error = ft_itoa(info->code_error);
	if (!code_error)
		exit_free_perror(NULL, ENV, info,
			BG_RED"memory allocation failed during parsing"RESET);
	len_code_error = ft_strlen(code_error);
	*line = ft_realloc(*line, len_line, len_line + 5 + 1);
	if (*line == NULL)
		exit_free_perror(NULL, ENV, info,
			BG_RED"memory allocation failed during parsing"RESET);
	ft_memcpy(*line + a->j, code_error, ft_strlen(code_error));
	a->i += j - a->i;
	free(code_error);
	return (len_code_error);
}
