/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstineau <vstineau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:55:25 by vstineau          #+#    #+#             */
/*   Updated: 2024/08/11 18:39:05 by vstineau         ###   ########.fr       */
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

char	*fill_heredoc(char *line, int fd)
{
	putline_fd(line, fd);
	free(line);
	line = readline(BHI_BLACK"> "RESET);
	if (!line)
		return (NULL);
	return (line);
}

char	*fill_heredoc2(char *line, t_cmd *c, char *s1)
{
	(void)s1;
	line = fill_heredoc(line, c->fd_h);
	if (!line)
	{
		c->error = 3;
	}
	return (line);
}
