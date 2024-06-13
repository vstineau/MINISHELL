
#include "../includes/minishell.h"

void	printlist(t_cmd *cmd)
{
	t_cmd *current;
	int i = 0;

	current = cmd;
	while (current)
	{
		printf("cmd nb %d = %s\n", i, current->cmd);
		printf("infile nb %d = %s\n", i, current->infile);
		printf("outfile nb %d = %s\n", i, current->outfile);
		printf("heredoc nb %d = %s\n", i, current->heredoc);
		printf("first arg nb %d = %s\n", i, current->arg[0]);
		i++;
		current = current->next;
	}
}


int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	t_cmd	*c;
	//struct sigaction	sig;

	c = (t_cmd *){0};
	//sigemptyset(&sig.sa_mask);
	//init_signals(&sig);
	char *line;
	char	prompt[4097];

	while (1)
	{
		line = readline(get_prompt(prompt));
		if (line)
			add_history(line);
		c = parse(line);
		//printlist(c);
	}
	return (0);
}
