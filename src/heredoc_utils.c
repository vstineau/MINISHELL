/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstineau <vstineau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:55:25 by vstineau          #+#    #+#             */
/*   Updated: 2024/08/12 15:16:33 by vstineau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	perror_and_return_i(t_minishell *info, char *s, int i)
{
	info->code_error = 2;
	perror(s);
	return (i);
}

static void	putline_fd(char *s, int fd)
{
	while (*s)
		write(fd, s++, 1);
	write(fd, "\n", 1);
}

char	*fill_heredoc(char *line, int fd, t_cmd *c)
{
	(void)fd;
	free(line);
	line = readline(BHI_BLACK"> "RESET);
	if (!line)
		return (NULL);
	line = expand_heredoc(line, c->i);
	return (line);
}

char	*fill_heredoc2(char *line, t_cmd *c, char *s1)
{
	(void)s1;
	putline_fd(line, c->fd_h);
	line = fill_heredoc(line, c->fd_h, c);
	if (!line)
	{
		c->error = 3;
	}
	return (line);
}

char	*expand_heredoc(char *line, t_minishell *info)
{
	char		*newline;
	t_iterator	a;

	newline = NULL;
	newline = ft_calloc(1, ft_strlen(line) + 1);
	if (newline == NULL)
		exit_free_perror(NULL, ENV, info,
			BG_RED"memory allocation failed during parsing"RESET);
	a = (t_iterator){0};
	while (line[a.i])
	{
		if (line[a.i] == '$' && is_num(line[a.i + 1]))
			a.j += expand_dols_number(line, &newline, &a);
		else if (line[a.i] == '$' && line[a.i + 1] == '?')
			a.j += expand_dols_qmark(line, &newline, info, &a);
		else if (line[a.i] == '$' && line[a.i + 1])
		{
			a.j += expand_env_v(line, &newline, info, &a);
			if (a.dols_end)
				a.j += get_dols(&newline, &a, info);
		}
		else if (line[a.i])
			newline[a.j++] = line[a.i++];
	}
	return (free(line), newline);
}
