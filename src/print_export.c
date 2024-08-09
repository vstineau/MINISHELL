/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstineau <vstineau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:55:54 by vstineau          #+#    #+#             */
/*   Updated: 2024/08/09 14:57:48 by vstineau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	apply_print_export(char *env, int fd, int j)
{
	int	len;

	len = ft_strlen(env);
	ft_putstr_fd("export ", fd);
	while (env[j] != '=' && j < len)
	{
		ft_putchar_fd(env[j], fd);
		j++;
	}
	j++;
	if (ft_strchr(env, '=') != NULL)
	{
		ft_putstr_fd("=\"", fd);
		while (j < len)
		{
			ft_putchar_fd(env[j], fd);
			j++;
		}
		ft_putstr_fd("\"", fd);
	}
	ft_putstr_fd("\n", fd);
	j = 0;
}

char	**ft_print_export(char **env, int fd)
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
		apply_print_export(env[i], fd, j);
		i++;
	}
	if (fd != 1)
		close (fd);
	free_split(env);
	return (env2);
}
