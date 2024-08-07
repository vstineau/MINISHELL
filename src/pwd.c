
#include "../includes/minishell.h"

void	check_arg_pwd(t_cmd *c)
{
	if (c->arg[0][0] == '-')
	{
		if (c->arg[0][1] == '-')
		{
			if ((c->arg[0][2] >= 32) && c->arg[0][2] < 127)
			{
				ft_putstr_fd("pwd: ", 2);
				write(2, &c->arg[0][0], 1);
				write(2, &c->arg[0][1], 1);
				ft_putstr_fd(": invalid option\n", 2);
				c->i->code_error = 2;
				return ;
			}
		}
		if ((c->arg[0][1] >= 32 && c->arg[0][1] < 127) && c->arg[0][1] != '-')
		{
			ft_putstr_fd("pwd: ", 2);
			write(2, &c->arg[0][0], 1);
			write(2, &c->arg[0][1], 1);
			ft_putstr_fd(": invalid option\n", 2);
			c->i->code_error = 2;
			return ;
		}

	}
}



void	pwd(int fd, t_cmd *c)
{
	char	*pwd;
	
	if (c->arg[0] != NULL)
		check_arg_pwd(c);
	if (c->i->code_error == 2)
		return ;
	pwd = getcwd(NULL, 0);
	ft_putstr_fd(pwd, fd);
	ft_putstr_fd("\n", fd);
	free(pwd);
	if (fd != 1)
		close (fd);
}
