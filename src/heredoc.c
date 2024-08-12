/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstineau <vstineau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:55:18 by vstineau          #+#    #+#             */
/*   Updated: 2024/08/12 12:06:54 by aroualid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	close_heredoc(t_cmd *c, char *line, int *fd)
{
	if (*fd != -1)
		close(*fd);
	*fd = -1;
	free(line);
	c->infile = "/tmp/heredoc";
}

//put the heredoc key in the key[4096]
static int	fill_key_heredoc(char key[4096], char *s, int *i, t_cmd *c)
{
	int	j;

	j = 0;
	while (s[*i] && check_char(s[*i], "'\" \t"))
		*i += 1;
	while (s[*i] && !check_char(s[*i], "'\" \t"))
	{
		key[j] = s[*i];
		if (check_char(key[j + 1], "<>"))
		{
			c->error = 1;
			c->i->code_error = 3;
		}
		*i += 1;
		j++;
	}
	if (s[*i] == '"' || s[*i] == '\'')
		*i += 1;
	if (c->error)
		return (0);
	return (1);
}

//no $ENV_VAR should be expand in heredoc key
void	no_expand_heredoc(char *s, char *line, t_iterator *a)
{
	int	i;
	int	j;

	line[a->j++] = s[a->i];
	line[a->j++] = s[a->i++];
	i = 1;
	j = 0;
	while (s[a->i + i + j] && check_char(s[a->i + i + j], " \t"))
		j++;
	while (s[a->i + i + j] && !check_char(s[a->i + i + j], " \t"))
	{
		(line + a->j)[i - 1] = (s + a->i)[i + j];
		i++;
	}
	a->i += i + j;
	a->j += i - 1;
}

/*get the heredoc key then use readline to write in a temporary file until
the key is printed or a ctrl c / ctrl d hapenned */
int	heredoc(char *s, t_cmd *c, t_minishell *info, char *s1)
{
	char	key[4096];
	char	*line;
	int		i;

	ft_memset(key, 0, 4096);
	i = 0;
	while (check_char(s[i], " \t"))
		i++;
	if (!s[i])
		return (perror_and_return_i(info, BG_RED"syntax error"RESET, i));
	if (!fill_key_heredoc(key, s, &i, c))
		return (i);
	line = readline(BHI_BLACK"> "RESET);
	if (!line)
	{
		free(s1);
		exit_free_perror(c, ENV, info, NULL);
	}
	c->fd_h = open("/tmp/heredoc", O_WRONLY | O_CREAT | O_TRUNC);
	while (!c->error && ft_strcmp(key, line) && g_signal_received != SIGINT)
		line = fill_heredoc2(line, c, s1);
	close_heredoc(c, line, &c->fd_h);
	if (g_signal_received == SIGINT)
		c->error = 2;
	return (i);
}

//just get the infile name and keep it in t_cmd *c
int	no_heredoc(char *s, t_cmd *c, t_minishell *info)
{
	int	i;
	int	j;

	if (c->infile)
		free(c->infile);
	c->infile = ft_calloc(ft_strlen(s) + 1, 1);
	if (!c->infile)
		exit_free_perror(c, ENV, info,
			BG_RED"memory allocation failed during parsing"RESET);
	i = 0;
	j = 0;
	while (s[i] && check_char(s[i], "  \t"))
		i++;
	while (s[i] && !check_char(s[i], "  \t|><$"))
		c->infile[j++] = s[i++];
	if (s[i] && check_char(s[i], "<>"))
		set_error_code(c, 2);
	return (i);
}
