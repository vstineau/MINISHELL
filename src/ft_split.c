
#include "../includes/minishell.h"

static	int	fill_words(char const *s, char c, char **split, size_t count)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	while (s[i] && k < count)
	{
		while (s[i] == c && s[i])
			i++;
		j = i;
		while (s[j] != c && s[j])
			j++;
		split[k] = ft_calloc((j - i + 1), (sizeof(char)));
		if (!split[k])
			return (0);
		j = 0;
		while (s[i] != c && s[i])
			split[k][j++] = s[i++];
		k++;
	}
	return (1);
}

static void	free_all(char **split, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	count_arg(char *s)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while(s[i])
	{
		while (s[i] && (s[i] == ' ' || s[i] == '\t'))
			i++;
		if (s[i] &&  (s[i] != ' ' || s[i] != '\t'))
			count++;
		while (s[i] && (s[i] != ' ' && s[i] != '\t'))
			i++;
	}
	return (count);
}

size_t	count_words(char const *s, char c)
{
	size_t	l;
	size_t	i;

	i = 0;
	l = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
			l++;
		while (s[i] != c && s[i])
			i++;
	}
	return (l);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	count;

	if (!s)
		return (NULL);
	count = count_words(s, c);
	split = ft_calloc((count + 1), (sizeof(char *)));
	if (split == 0)
		return (NULL);
	if (!(fill_words(s, c, split, count)))
	{
		free_all(split, count);
		return (NULL);
	}
	return (split);
}

