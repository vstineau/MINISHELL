
#include "../includes/minishell.h"

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

char	*ft_strncpy(char *dest, char *src, int n)
{
	int	i;

	i = 0;
	while (src[i] && i < n)
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

int	check_infile(char *file)
{
	int		infile;

	infile = open(file, O_RDONLY);
	if (infile == -1)
	{
		perror(file);
		return (infile);
	}
	return (infile);
}

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;

	ptr = (char *)s;
	while (*ptr != (char) c)
	{
		if (*ptr == '\0')
		{
			return (NULL);
		}
		ptr++;
	}
	return (ptr);
}


void	ft_close(int pip[2], int infile)
{
	close (pip[1]);
	close (pip[0]);
	close (infile);
}

char	*return_path(char **cmd, char *endfile, char *path)
{
	free_split(cmd);
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

char	*free_return(char **cmd, char *endfile)
{	
	free_split(cmd);
	free(endfile);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
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

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (s == NULL)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_sort_strings(int num, char **s)
{
	int		i;
	int		j;
	char	*temp;

	i = 1;
	j = 0;
	while (i < num)
	{
		j = i;
		while (j > 0 && ft_strcmp(s[j - 1], s[j]) > 0)
		{
			temp = s[j - 1];
			s[j - 1] = s[j];
			s[j] = temp;
			j--;
		}
		i++;
	}
}
