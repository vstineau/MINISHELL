/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstineau <vstineau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:57:18 by vstineau          #+#    #+#             */
/*   Updated: 2024/08/13 14:56:47 by aroualid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <errno.h>

int	ft_putstr_fd(char *s, int fd, t_minishell *info)
{
	int	i;

	if (s == NULL)
		return (-1);
	i = 0;
	while (s[i] != '\0')
	{
		if (write(fd, &s[i], 1) == -1)
		{
			errno = ENOSPC;
			if (info->write_error == 0)
				perror ("");
			info->write_error = 1;
			info->code_error = 1;
			return (-1);
		}
		i++;
	}
	return (0);
}

void	ft_sort_strings(int num, char **s)
{
	int		i;
	int		j;
	char	*temp;

	i = 1;
	j = 0;
	while (i < num)
	{
		j = i;
		while (j > 0 && ft_strcmp(s[j - 1], s[j]) > 0)
		{
			temp = s[j - 1];
			s[j - 1] = s[j];
			s[j] = temp;
			j--;
		}
		i++;
	}
}

void	set_error_code(t_cmd *c, int code)
{
	c->i->code_error = code;
	c->error = 1;
}

static void	check_unwanted_char_arg(t_cmd *c, t_cmd *cfirst)
{
	int	i;
	int	j;

	i = 0;
	while (c->arg[i])
	{
		j = 0;
		while (c->arg[i][j])
		{
			if (!check_char(c->arg[i][j], "&;()"))
				break ;
			j++;
		}
		if (!c->arg[i][j] && !is_blank(c->arg[i]))
			set_error_code(cfirst, 2);
		i++;
	}
}

void	check_unwanted_char_cmd(t_cmd *c)
{
	t_cmd	*current;
	int		i;

	current = c;
	while (current)
	{
		i = 0;
		while (current->cmd && current->cmd[i])
		{
			if (!check_char(current->cmd[i], "&;()"))
				break ;
			i++;
		}
		if (current->cmd && !current->cmd[i])
			set_error_code(c, 2);
		check_unwanted_char_arg(current, c);
		current = current->next;
		while (current && current->pipe == PIPE)
			current = current->next;
	}
}
