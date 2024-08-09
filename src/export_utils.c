/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstineau <vstineau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:54:49 by vstineau          #+#    #+#             */
/*   Updated: 2024/08/09 18:02:07 by aroualid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

int	ft_isalnum(int c)
{
	if (((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) || (c >= 48 && c <= 57))
		return (1);
	return (0);
}

int	arg_ok_for_export(char *av)
{
	int	i;
	int	len;

	len = 0;
	i = 1;
	if (ft_strchr(av, '=') != NULL)
	{
		while (av[len] != '=')
			len++;
	}
	else
		len = ft_strlen(av);
	while (av[i] && i < len)
	{
		if (ft_isalnum(av[i]) == 1 || av[i] == '_')
			i++;
		else if (i + 1 == len && av[i] == '+')
			i++;
		else
			return (0);
	}
	return (1);
}

char	*get_first_av2(char *av)
{
	char	*av1;
	int		i;
	int		len;
		
	i = 0;
	len = ft_strlen(av);
	while (av[i] != '+' && i < len)
		i++;
	av1 = malloc(sizeof(char) * len + 1);
	ft_strncpy(av1, av, i);
	return (av1);
}

char	*get_first_av(char *av, t_cmd *c)
{
	char	*av1;
	int		i;
	int		len;
	char	*test;

	i = 0;
	if ((ft_isalpha(av[0]) == 0 && av[0] != '_') || arg_ok_for_export(av) == 0)
		return (wrong_identifier(av, c, "export"));
	len = ft_strlen(av);
	test = ft_strchr(av, '+');
	if (test != NULL && test[1] == '=')
		return (av1 = get_first_av2(av));
	if (ft_strchr(av, '=') == NULL)
	{
		av1 = malloc(sizeof(char) * len + 2);
		ft_strcpy(av1, av);
		av1 = ft_strjoin (av1, "=");
		return (av1);
	}
	while (av[i] != '=' && i < len)
		i++;
	av1 = malloc(sizeof(char) * len + 1);
	ft_strncpy(av1, av, i);
	return (av1);
}
