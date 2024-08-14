/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils9.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstineau <vstineau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 09:21:39 by vstineau          #+#    #+#             */
/*   Updated: 2024/08/14 09:22:33 by vstineau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_and_exit_exec(t_cmd *c_first, t_cmd *c, int pip[2], int value)
{
	if (c->outfile != NULL)
		close (c->fd);
	close (pip[0]);
	free_cmd (c_first, ENV, c->i);
	exit (value);
}
