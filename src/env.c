/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstineau <vstineau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:53:54 by vstineau          #+#    #+#             */
/*   Updated: 2024/08/13 14:42:37 by aroualid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	error_message_env(t_cmd *c)
{
	if (c->arg[0] == NULL)
		return (0);
	if (c->arg[0][0] >= 97 && c->arg[0][0] <= 122)
	{
		return (1);
	}
	if (access(c->arg[0], X_OK != 0) && (c->arg[0][0] == '.'))
	{
		perror (c->arg[0]);
		return (126);
	}
	else if (c->arg [0][0] < 97 || c->arg[0][0] > 122)
	{
		ft_putstr_fd("‘", 2, c->i);
		ft_putstr_fd(c->arg[0], 2, c->i);
		ft_putstr_fd("’: No such file or directory\n", 2, c->i);
		return (127);
	}
	return (0);
}

void	our_env(char **env, int fd, t_cmd *c)
{
	int		i;
	char	*test;

	i = 0;
	c->i->code_error = error_message_env(c);
	if (c->i->code_error == 0)
	{
		while (env[i])
		{
			test = ft_strchr(env[i], '=');
			if (env[i] != NULL && test != NULL)
			{
				ft_putstr_fd(env[i], fd, c->i);
				ft_putstr_fd("\n", fd, c->i);
			}
			i++;
		}
		if (fd != 1)
			close (fd);
	}
}
