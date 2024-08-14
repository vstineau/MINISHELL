/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstineau <vstineau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:56:23 by vstineau          #+#    #+#             */
/*   Updated: 2024/08/14 09:34:12 by vstineau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	error_file(t_cmd *c, t_minishell *info)
{
	c->error = 1;
	info->code_error = 2;
}

static int	return_i(char c, int i)
{
	if (c == '"' || c == '\'')
		return (i + 1);
	return (i);
}

static int	get_outfile(char *s, t_cmd *c, t_minishell *info)
{
	int	i;
	int	j;

	if (c->outfile)
		free(c->outfile);
	c->outfile = ft_calloc(ft_strlen(s) + 1, 1);
	if (!c->outfile)
		exit_free_perror(c, ENV, info,
			BG_RED"memory allocation failed during parsing"RESET);
	i = 0;
	j = 0;
	while (s[i] && check_char(s[i], " \t'\"\n"))
	{
		if (s[i] == '"' || s[i] == '\'')
			c->outfile_quote ^= (1 << 1);
		i++;
	}
	while (s[i] && (!check_char(s[i], "<> |\t\n") || c->outfile_quote)
		&& !check_char(s[i], "'\""))
		c->outfile[j++] = s[i++];
	if (s[i] && (check_char(s[i], "<|>") && !c->outfile_quote))
		set_error_code(c, 2);
	if (is_blank(c->outfile))
		error_file(c, info);
	return (return_i(s[i], i));
}

int	infile(char *s, t_cmd *c, t_minishell *info)
{
	int	i;

	i = 0;
	if (*s && *(s + 1) == '\0')
	{
		info->code_error = 2;
		c->error = 1;
		return (1);
	}
	if (*s && *(s + 1) == '<')
	{
		i += 2;
		c->redirect = HEREDOC;
		if (*(s + 2) && *(s + 2) == '<')
			error_file(c, info);
		if (!c->error)
			i += heredoc(s + i, c, info, s);
	}
	else
	{
		i++;
		c->redirect = NO_HEREDOC;
		i += no_heredoc(s + i, c, info);
	}
	return (i);
}

int	outfile(char *s, t_cmd *c, t_minishell *info)
{
	int	i;

	i = 0;
	if (*s && *(s + 1) == '\0')
	{
		info->code_error = 2;
		c->error = 1;
		return (1);
	}
	if (*s && *(s + 1) == '>')
	{
		if (*(s + 2) == '\0')
			error_file(c, info);
		if (*(s + 2) && *(s + 2) == '>')
			error_file(c, info);
		i += 2;
		c->redirect = APPEND;
	}
	else
	{
		i++;
		c->redirect = NO_APPEND;
	}
	i += get_outfile(s + i, c, info);
	return (i);
}
