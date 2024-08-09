/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstineau <vstineau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:57:22 by vstineau          #+#    #+#             */
/*   Updated: 2024/08/09 14:57:48 by vstineau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_blank(char *s)
{
	int	i;

	if (!s)
		return (1);
	i = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	check_error(t_cmd *c)
{
	t_cmd	*current;

	current = c;
	while (current)
	{
		if (current->error == 1)
			return (1);
		if (current->error == 2)
			return (2);
		current = current->next;
	}
	return (0);
}

int	check_error_again(t_cmd *c)
{
	if (!is_blank(c->cmd) || !c->infile || c->outfile || c->infile)
		return (1);
	else
		return (0);
}

//check if an error occured during the parsing
int	check_before_exec(t_cmd *c, char *line)
{
	if (line)
		free(line);
	if (!c)
		return (0);
	if ((!is_blank(c->cmd) && !check_error(c)
			&& g_signal_received != SIGINT)
		|| (!is_blank(c->outfile) && !check_error(c)))
		return (1);
	else
		return (0);
}

int	get_dols(char **line, t_iterator *a, t_minishell *info)
{
	int	len_line;

	len_line = ft_strlen(*line);
	*line = ft_realloc(*line, len_line, len_line + 100);
	if (*line == NULL)
		exit_free_perror(NULL, ENV, info,
			BG_RED"memory allocation failed during parsing"RESET);
	ft_memcpy(*line + len_line, "$", 1);
	a->dols_end = false;
	a->i++;
	return (1);
}
