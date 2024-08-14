/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstineau <vstineau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:57:44 by vstineau          #+#    #+#             */
/*   Updated: 2024/08/13 17:50:00 by aroualid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	wait_status(t_minishell *info, int status)
{
	int	exit_status;

	exit_status = 0;
	if (WIFEXITED(status))
	{
		exit_status = WEXITSTATUS(status);
		info->code_error = exit_status;
	}
}

int	taille_node(t_cmd *c)
{
	t_cmd	*test;
	int		taille;

	test = c;
	taille = 0;
	while (test)
	{
		if (test->cmd != NULL)
			taille++;
		test = test->next;
	}
	return (taille);
}

void	apply_wait(t_cmd *c, t_minishell *info)
{
	int		taille;
	int		pid_return;
	int		i;
	int		status;

	i = 0;
	pid_return = 0;
	taille = taille_node(c);
	if (c->i->is_builtin == 1)
	{
		while (wait(&status) > 0)
			wait_status(info, status);
	}
	else
	{
		while (i < taille)
		{
			pid_return = (wait(&status));
			if (pid_return < 0)
				continue ;
			if (pid_return == c->i->last_pid)
				wait_status(info, status);
			i++;
		}
	}
}

int	xcd(int c)
{
	if ((c == '=') || (c == '\0'))
		return (1);
	return (0);
}
