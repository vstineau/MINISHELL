
#include "../includes/minishell.h"
#include <stdio.h>

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

static int	free_cmd2(t_cmd *cmd, bool env, t_minishell *info)
{
	t_cmd	*temp;

	if (env)
		free_split(info->env);
	while (cmd)
	{
		temp = cmd;
		if (cmd->cmd)
		{
			printf("cmd = %s\n", cmd->cmd);
			free(cmd->cmd);
		}
		if (cmd->infile && cmd->redirect == NO_HEREDOC)
			free(cmd->infile);
		if (cmd->outfile)
			free(cmd->outfile);
		free_split(cmd->arg);
		cmd = cmd->next;
		free(temp);
	}
	unlink("heredoc");
	cmd = NULL;
	return (0);
}

void	our_exit(t_cmd *c, t_minishell *info)
{
	int			i;
	__int128	atoi_crack;
	int			value;

	value = 0;
	i = 0;
	if (c->arg[0] == NULL)
		exit(free_cmd2(c, ENV, info));
	atoi_crack = ato__i128(c->arg[0]);
	printf("\n");
	if (c->arg[0][0] == '-')
		i = 1;
	while (i < ft_strlen(c->arg[0]))
	{
		if (ft_isdigit(c->arg[0][i]) == 1)
			i++;
		else
			exit (2);
	}
	if ((atoi_crack > LLONG_MAX || atoi_crack < LLONG_MIN)
		&& (ft_strlen(c->arg[0]) > 20))
		exit(2);
	value = (atoi_crack % 256);
	free_cmd(c, ENV, info);
	exit (value);
}
