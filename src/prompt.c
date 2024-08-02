
#include "../includes/minishell.h"

static int	leni(long int n)
{
	long int	c;
	long int	j;
	long int	nb;

	j = 1;
	c = n;
	nb = n;
	if (nb < 0)
		c *= -1;
	while (c >= 10)
	{
		c = c / 10;
		j++;
	}
	if (nb < 0)
		j++;
	return (j);
}

static char	*zero(char *dest)
{
	dest[0] = '0';
	return (dest);
}

char	*ft_itoa(int n)
{
	long int		nb;
	int				l;
	char			*dest;

	nb = n;
	l = leni(nb);
	dest = malloc(sizeof(char) * (l + 1));
	if (!dest)
		return (NULL);
	dest[l--] = '\0';
	if (nb == 0)
		return (zero(dest));
	if (nb < 0)
	{
		dest[0] = '-';
		nb *= -1;
	}
	while (nb != 0)
	{
		dest[l--] = (nb % 10) + 48;
		nb = nb / 10;
	}
	return (dest);
}

char	*get_prompt(char *prompt, t_minishell *info, t_cmd *c)
{
	int		i;
	int		j;
	char	p[4096];
	char	*s;

	s = ft_itoa(info->code_error);
	if (!s)
		exit_free_perror(c, ENV, info,
			BG_RED"memory allocation failed during parsing"RESET);
	getcwd(prompt, 4097);
	ft_strcpy(p, prompt);
	i = ft_strlen(prompt);
	j = leni(info->code_error);
	ft_strcpy(prompt + j, p);
	ft_memcpy(prompt, s, j);
	free(s);
	ft_strcpy(prompt + i + j, BHI_GREEN"\001\u279C\002 "RESET);
	return (prompt);
}
