/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstineau <vstineau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:55:54 by vstineau          #+#    #+#             */
/*   Updated: 2024/08/13 14:37:45 by aroualid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_putchar_fd(char d, int fd, t_cmd *c)
{
	if (write(fd, &d, 1) == -1)
	{
		c->i->code_error = 1;
		return (-1);
	}
	return (0);
}

void	apply_print_export(char *env, int fd, int j, t_cmd *c)
{
	int	len;

	len = ft_strlen(env);
	ft_putstr_fd("export ", fd, c->i);
	while (env[j] != '=' && j < len)
	{
		ft_putchar_fd(env[j], fd, c);
		j++;
	}
	j++;
	if (ft_strchr(env, '=') != NULL)
	{
		ft_putstr_fd("=\"", fd, c->i);
		while (j < len)
		{
			ft_putchar_fd(env[j], fd, c);
			j++;
		}
		ft_putstr_fd("\"", fd, c->i);
	}
	ft_putstr_fd("\n", fd, c->i);
	j = 0;
}

char	**ft_print_export(char **env, int fd, t_cmd *c)
{
	int		i;
	char	**env2;
	int		len;
	int		j;

	j = 0;
	len = env_size(env);
	i = 0;
	env2 = get_env(env, NULL, 0);
	ft_sort_strings(len, env);
	while (env[i])
	{
		apply_print_export(env[i], fd, j, c);
		i++;
	}
	if (fd != 1)
		close (fd);
	free_split(env);
	return (env2);
}
