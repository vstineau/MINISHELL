
#include "../includes/minishell.h"

void exec(t_cmd *c, char **envp)
{
	cd(c->arg[0], envp);
	
}
