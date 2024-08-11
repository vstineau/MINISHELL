/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstineau <vstineau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:53:49 by vstineau          #+#    #+#             */
/*   Updated: 2024/08/11 12:15:59 by vstineau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	cmd_get_quote(char *s, t_cmd *c, int j)
{
	char	quote;
	int		i;

	i = 1;
	if (*s == '\'')
		quote = '\'';
	else
		quote = '"';
	while (s[i] && s[i] != quote)
		c->cmd[j++] = s[i++];
	if (s[i] != quote)
	{
		set_error_code(c, 2);
	}
	return (i);
}

static int	arg_get_quote(char *s, t_cmd *c, int iarg, int j)
{
	char	quote;
	int		i;

	i = 1;
	if (*s == '\'')
		quote = '\'';
	else
		quote = '"';
	while (s[i] && s[i] != quote)
		c->arg[iarg][j++] = s[i++];
	if (s[i] != quote)
	{
		set_error_code(c, 2);
	}
	return (i);
}

static int	if_cmd(char *s, t_cmd *c, int *i_arg, t_minishell *info)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
		i++;
	c->arg[*i_arg] = ft_calloc(i + 1, 1);
	if (!c->arg[*i_arg])
		exit_free_perror(c, ENV, info,
			BG_RED"memory allocation failed during parsing\n"RESET);
	i = 0;
	j = 0;
	while (!c->error && s[i] && s[i] != ' ' && s[i] != '\t' && s[i] != '|')
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			i += arg_get_quote(s + i, c, *i_arg, i) + 1;
			j = i - 2;
		}
		else
			c->arg[*i_arg][j++] = s[i++];
	}
	*i_arg += 1;
	return (i);
}

/*catch the command and put it in t_cmd *c->cmd 
if cmd exist fill the t_cmd arg[i]*/
int	get_cmd(char *s, t_cmd *c, int *i_arg, t_minishell *info)
{
	int	i;
	int	j;

	if (!c->cmd)
	{
		i = ft_strlen(s);
		c->cmd = ft_calloc(i + 1, 1);
		if (!c->arg)
			exit_free_perror(c, ENV,
				info, BG_RED"memory allocation failed during parsing\n"RESET);
		i = 0;
		j = 0;
		while (!c->error && s[i] && s[i] != ' ' && s[i] != '\t' && s[i] != '|')
		{
			if (s[i] == '\'' || s[i] == '"')
			{
				i += cmd_get_quote(s + i, c, i) + 1;
				j = i - 2;
			}
			else
				c->cmd[j++] = s[i++];
		}
		return (i);
	}
	return (if_cmd(s, c, i_arg, info));
}
