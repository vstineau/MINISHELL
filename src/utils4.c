/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstineau <vstineau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:57:08 by vstineau          #+#    #+#             */
/*   Updated: 2024/08/09 14:57:48 by vstineau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*return_path(char *endfile, char *path)
{
	free(endfile);
	return (path);
}

int	exit_close(int pip[2])
{
	close(pip[1]);
	close(pip[0]);
	exit (-1);
}

void	free_alls(char *path, char **cmd)
{
	free_split(cmd);
	free(path);
}

char	*free_return(char *endfile)
{	
	free(endfile);
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		t1;
	int		t2;
	char	*ptr;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	j = 0;
	i = 0;
	t1 = ft_strlen((char *)s1);
	t2 = ft_strlen((char *)s2);
	ptr = ft_calloc(t1 + t2 + 1, 1);
	if (!ptr)
		return (free (ptr), NULL);
	while (i < (t1 + t2))
	{
		while (i < t1)
			if (i++ >= 0)
				ptr[i - 1] = s1[i - 1];
		while (j < t2)
			ptr[i++] = s2[j++];
	}
	return (ptr);
}
