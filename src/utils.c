/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstineau <vstineau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:56:47 by vstineau          #+#    #+#             */
/*   Updated: 2024/08/09 14:57:48 by vstineau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	char			*dest1;
	const char		*src1;

	if (!dest && !src)
		return (dest);
	i = 0;
	dest1 = dest;
	src1 = src;
	while (i < n)
	{
		dest1[i] = src1[i];
		i++;
	}
	return (dest1);
}

int	ft_strncmp( const char *first, const char *second, size_t length)
{
	unsigned int	i;

	i = 0;
	if (length == 0)
		return (0);
	while (first[i] == second[i] && i < length - 1 && first[i])
	{
		i++;
	}
	return (((unsigned char *)first)[i] - ((unsigned char *)second)[i]);
}

int	is_uppercase(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	else
		return (0);
}

int	check_char(char c, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	*ft_realloc(void *old, size_t old_length, size_t new_length)
{
	void	*new_ptr;

	new_ptr = ft_calloc(new_length, 1);
	if (new_ptr == NULL)
		return (NULL);
	if (old == NULL)
		return (new_ptr);
	ft_memcpy(new_ptr, old, old_length);
	free(old);
	return (new_ptr);
}
