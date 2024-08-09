/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstineau <vstineau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:55:47 by vstineau          #+#    #+#             */
/*   Updated: 2024/08/09 14:57:48 by vstineau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_cmd	*ft_lstnew(char *s, t_cmd *c, t_minishell *info)
{
	t_cmd	*new_cmd;

	new_cmd = NULL;
	new_cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!new_cmd)
	{
		free_cmd(c, ENV, info);
		perror(BG_RED"memory allocation failed during parsing"RESET);
		exit(1);
	}
	new_cmd->arg = NULL;
	new_cmd->i = info;
	new_cmd->arg = ft_calloc((count_arg(s) + 1), sizeof(char *));
	if (!new_cmd->arg)
	{
		free_cmd(c, ENV, info);
		free(new_cmd);
		perror(BG_RED"memory allocation failed during parsing"RESET);
		exit(1);
	}
	s += 1;
	return (new_cmd);
}

static void	ft_lstadd_back(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*current;
	t_cmd	*previous;

	if (!new)
		return ;
	if (!*cmd)
	{
		*cmd = new;
		return ;
	}
	current = *cmd;
	while (current)
	{
		previous = current;
		current = current->next;
	}
	previous->next = new;
}

static int	get_pipe(char *s, int *i, t_cmd **current, t_minishell *info)
{
	*i = 0;
	ft_lstadd_back(current, ft_lstnew(s, *current, info));
	*current = (*current)->next;
	(*current)->pipe = PIPE;
	ft_lstadd_back(current, ft_lstnew(s, *current, info));
	*current = (*current)->next;
	return (1);
}

static int	skip_space(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	return (i);
}

t_cmd	*parse(char *s, t_minishell *info)
{
	t_cmd	*c;
	t_cmd	*current;
	int		i_arg;

	if (!s || (s && is_blank(s)))
		return (NULL);
	i_arg = 0;
	c = NULL;
	c = ft_lstnew(s, c, info);
	current = c;
	while (!c->error && *s)
	{
		s += skip_space(s);
		if (*s == '<' && !c->error)
			s += infile(s, current, info);
		else if (*s == '>' && !c->error)
			s += outfile(s, current, info);
		else if (*s == '|' && !c->error)
			s += get_pipe(s, &i_arg, &current, info);
		else
			s += get_cmd(s, current, &i_arg, info);
		if (!c->error)
			s += skip_space(s);
	}
	return (c);
}
