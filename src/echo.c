
#include "../includes/minishell.h"

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

int	check_echo_args(char *av)
{
	int		i;
	int		len;

	len = ft_strlen(av);
	i = 1;
	if (ft_strncmp(av, "-", 1) == 0)
	{
		while (i < len)
		{
			if (av[i] == 'n')
				i++;
			else
				return (0);
		}
		return (1);
	}
	return (0);
}

void	echo(char **av)
{
	int	i;

	i = check_echo_args(av[0]);
	while (av[i] != NULL)
	{
		printf("%s", av[i]);
		if (av[i + 1] != NULL)
			printf(" ");
		i++;

	}
	if (check_echo_args(av[0]) != 1)
		printf("\n");
}
