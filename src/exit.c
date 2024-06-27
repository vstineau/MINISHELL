
#include "../includes/minishell.h"
#include <stdio.h>
//#include <inttypes.h>

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

__int128	ato__i128(const char *str)
{
	int			i;
	int			signe;
	__int128	resultat;

	i = 0;
	signe = 1;
	resultat = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\t' || str[i] == '\v')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			signe *= -1;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		resultat *= 10;
		resultat += str[i] - '0';
		i++;
	}
	return (resultat * signe);
}

/*void print_uint128(__int128 value) {
    if (value < 0) {
        putchar('-');
        value = -value;
    }
    
    uint64_t high = value >> 64;
    uint64_t low = value & 0xFFFFFFFFFFFFFFFF;

    if (high == 0) {
        printf("%" PRIu64, low);
    } else {
        printf("%" PRIu64 "%018" PRIu64, high, low);
    }
}*/

//void    our_exit(t_cmd *c, t_minishell *info, char *error_code)
void	our_exit(char **env, char *error_code)
{
	int			i;
	__int128	atoi_crack;
	int			value;

	value = 0;
	atoi_crack = ato__i128(error_code);
	//__int128 num = (__int128)atoi_crack;
    //print_uint128(num);
	printf("\n");
	free_cmd(c, ENV, info);
	if (error_code[0] == '-')
		i = 1;
	else
		i = 0;
	while (i < ft_strlen(error_code))
	{
		if (ft_isdigit(error_code[i]) == 1)
			i++;
		else
			exit (2);
	}
	if ((atoi_crack > LLONG_MAX || atoi_crack < LLONG_MIN) 
		&& (ft_strlen(error_code) > 20))
		exit (2);
	value = (atoi_crack % 256);
	//printf("%i\n", value);
	exit (value);
}

int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	our_exit(env, "9223372036854775807");
}
