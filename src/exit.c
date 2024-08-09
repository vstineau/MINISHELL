/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstineau <vstineau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:54:16 by vstineau          #+#    #+#             */
/*   Updated: 2024/08/09 15:48:51 by aroualid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

__int128	ato__i128(const char *str)
{
	int			i;
	int			signe;
	__int128	resultat;

	i = 0;
	signe = 1;
	resultat = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\t' || str[i] == '\v')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			signe *= -1;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		resultat *= 10;
		resultat += str[i] - '0';
		i++;
	}
	return (resultat * signe);
}

void	to_many_arg(t_cmd *c)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("exit: too many arguments\n", 2);
	c->i->code_error = 1;
	return ;
}

void	our_exit(t_cmd *c, t_cmd *c_first, int pip[2], int fd)
{
	int				i;
	__int128		atoi_crack;
	int				value;

	value = 0;
	i = 0;
	if (c->arg[0] == NULL)
		free_and_close(fd, pip, c_first, 0);
	if (c->arg[1] != NULL)
		return (to_many_arg(c));
	atoi_crack = ato__i128(c->arg[0]);
	if (c->arg[0][0] == '-')
		i = 1;
	while (i < ft_strlen(c->arg[0]))
	{
		if (ft_isdigit(c->arg[0][i]) == 1)
			i++;
		else
			free_and_close(fd, pip, c_first, 2);
	}
	if ((atoi_crack > LLONG_MAX || atoi_crack < LLONG_MIN)
		&& (ft_strlen(c->arg[0]) > 20))
		free_and_close(fd, pip, c_first, 2);
	value = (atoi_crack % 256);
	free_and_close(fd, pip, c_first, value);
}
