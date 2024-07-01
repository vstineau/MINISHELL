
#include "../includes/minishell.h"

/*void	swap_elements(char **tab, unsigned int p1, unsigned int p2)
{
	int tmp = tab[p1][0];
	tab[p1][0] = tab[p2][0];
	tab[p2] = tmp;
}

void	bubble_sort(char **tab, unsigned int size)
{
	unsigned int i = 0;
	unsigned int j = 0;

	while (i < size)
	{
		j = 0;
		while (j < size - 1)
		{
			if (tab[j] > tab[j + 1])
				swap_elements(tab, j, j + 1);
			j++;
		}
		i++;
	}
}

void	sort_int_tab(char **tab, unsigned int size)
{
	if (size <= 1)
		return ;
	bubble_sort(tab, size);
}*/

void ft_sort_strings(int num, char **s)
{
    int		i;
	int		j;
	char	*temp;

	i = 1;
	j = 0;
    while (i < num)
    {
		j = i;
        while (j > 0 && ft_strcmp(s[j-1], s[j]) > 0)
        {
            temp = s[j-1];
            s[j-1] = s[j];
            s[j] = temp;
			j--;
		}
		i++;
	}
}
