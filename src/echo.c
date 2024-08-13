/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstineau <vstineau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:53:42 by vstineau          #+#    #+#             */
/*   Updated: 2024/08/13 14:41:01 by aroualid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_echo_args(char *av, int pos)
{
	int		i;
	int		len;

	len = ft_strlen(av);
	i = 1;
	if (ft_strncmp(av, "-", 1) == 0)
	{
		while (i < len)
		{
			if (av[i] == 'n')
				i++;
			else
				return (pos);
		}
		return (pos + 1);
	}
	return (pos);
}

void	close_fd(int fd)
{
	if (fd != 1)
		close (fd);
}

void	echo(char **av, int fd, t_cmd *c)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (av)
	{
		while (av[j])
		{
			i = check_echo_args(av[i], i);
			if (j == i)
				break ;
			j++;
		}
		while (av[i] != NULL)
		{
			ft_putstr_fd(av[i], fd, c->i);
			if (av[i + 1] != NULL)
				ft_putstr_fd(" ", fd, c->i);
			i++;
		}
	}
	if (av[0] == NULL || check_echo_args(av[0], 0) == 0)
		ft_putstr_fd("\n", fd, c->i);
	close_fd(fd);
}
