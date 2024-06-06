
#include "../includes/minishell.h"

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
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
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

