/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstineau <vstineau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:56:09 by vstineau          #+#    #+#             */
/*   Updated: 2024/08/13 14:39:41 by aroualid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_arg_pwd(t_cmd *c)
{
	if (c->arg[0][0] == '-')
	{
		if (c->arg[0][1] == '-')
		{
			if ((c->arg[0][2] >= 32) && c->arg[0][2] < 127)
			{
				ft_putstr_fd("pwd: ", 2, c->i);
				write(2, &c->arg[0][0], 1);
				write(2, &c->arg[0][1], 1);
				ft_putstr_fd(": invalid option\n", 2, c->i);
				c->i->code_error = 2;
				return ;
			}
		}
		if ((c->arg[0][1] >= 32 && c->arg[0][1] < 127) && c->arg[0][1] != '-')
		{
			ft_putstr_fd("pwd: ", 2, c->i);
			write(2, &c->arg[0][0], 1);
			write(2, &c->arg[0][1], 1);
			ft_putstr_fd(": invalid option\n", 2, c->i);
			c->i->code_error = 2;
			return ;
		}
	}
}

void	pwd(int fd, t_cmd *c)
{
	char	*pwd;

	if (c->arg[0] != NULL)
		check_arg_pwd(c);
	if (c->i->code_error == 2)
		return ;
	pwd = getcwd(NULL, 0);
	ft_putstr_fd(pwd, fd, c->i);
	ft_putstr_fd("\n", fd, c->i);
	free(pwd);
	if (fd != 1)
		close (fd);
}
