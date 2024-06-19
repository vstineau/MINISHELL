
#include "../includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t		i;
	char		*s1;

	s1 = s;
	i = 0;
	while (i < n)
	{
		s1[i] = c;
		i++;
	}
	return (s1);
}

char	*ft_strcpy(char *dest, char *src)
{
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (dest);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*s;

	if (nmemb == 0 || size == 0)
		return (malloc(1));
	if ((ULONG_MAX / nmemb) < size)
		return (NULL);
	s = malloc(nmemb * size);
	if (s == NULL)
		return (NULL);
	ft_memset(s, 0, nmemb * size);
	return (s);
}

int	ft_strlen(char *s)
{
	int	i ;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void    *ft_memcpy(void *dest, const void *src, size_t n)
{
    size_t        i;
    char        *dest1;
    const char    *src1;

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

void    *ft_realloc(void *old, size_t old_length, size_t new_length)
{
    void    *new_ptr;

    new_ptr = ft_calloc(new_length, 1);
    if (new_ptr == NULL)
        return (NULL);
    if (old == NULL)
        return (new_ptr);
    ft_memcpy(new_ptr, old, old_length);
    free(old);
    return (new_ptr);
}

char    *ft_strdup(char *s)
{
    size_t    i;
    char    *dst;

    i = 0;
    dst = malloc(sizeof(char) * ft_strlen(s) + 1);
    if (dst == 0)
        return (NULL);
    while (s[i])
    {
        dst[i] = s[i];
        i++;
    }
    dst[i] = '\0';
    return (dst);
}
