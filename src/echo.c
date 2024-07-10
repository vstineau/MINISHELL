
#include "../includes/minishell.h"

int	check_echo_args(char *av, int pos)
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
				return (pos);
		}
		return (pos + 1);
	}
	return (pos);
}

void	echo(char **av, int fd)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (av[j])
	{
		i = check_echo_args(av[i], i);
		if (j == i)
			break ;
		j++;
	}
	while (av[i] != NULL)
	{
		ft_putstr_fd(av[i], fd);
		if (av[i + 1] != NULL)
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (check_echo_args(av[0], 0) == 0)
		ft_putstr_fd("\n", fd);	
	if (fd != 1)
		close (fd);
}

/*int	main(int ac, char **av)
{
	echo(av, 1);
	(void) ac;
}*/
