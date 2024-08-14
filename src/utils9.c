/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils9.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstineau <vstineau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 09:21:39 by vstineau          #+#    #+#             */
/*   Updated: 2024/08/14 10:29:55 by aroualid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <unistd.h>

void	free_and_exit_exec(t_cmd *c_first, t_cmd *c, int pip[2], int value)
{
	if (c->outfile != NULL)
		close (c->fd);
	close (pip[0]);
	free_cmd (c_first, ENV, c->i);
	exit (value);
}

void	open_outfile(t_cmd *c)
{
	c->fd = open(c->outfile, O_DIRECTORY);
	if (c->fd == -1)
	{
		if (c->redirect == APPEND)
		{
			c->fd = open(c->outfile, O_APPEND | O_CREAT | O_WRONLY, 0644);
			if (c->fd == -1)
				close (c->fd);
		}
		else
		{
			c->fd = open(c->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (c->fd == -1)
				close (c->fd);
		}
	}
	else
	{	
		close (c->fd);
		c->i->code_error = 1;
	}
}
