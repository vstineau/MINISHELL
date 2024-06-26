
#include "../includes/minishell.h"

int g_signal_received;

void	printlist(t_cmd *cmd)
{
	t_cmd *current;
	int i = 0;
	int j = 0;

	current = cmd;
	while (current)
	{
		printf("cmd nb %d = %s\n", i, current->cmd);
		printf("infile nb %d = %s\n", i, current->infile);
		printf("outfile nb %d = %s\n", i, current->outfile);
		while (current->arg[j])
			printf("first arg nb %d = %s\n", i, current->arg[j++]);
		i++;
		current = current->next;
	}
}

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	t_minishell info;
	t_cmd	*c;
	struct sigaction	sig;

	c = (t_cmd *){0};
	info = (t_minishell){0};
	info.env = get_env(envp);
	sigemptyset(&sig.sa_mask);
	init_signals(&sig);
	char *line;
	char	prompt[4097];
	int i = 0;
	while (1)
	{
		check_signal(&info);
		line = readline(get_prompt(prompt, &info));
		if (line)
		{
			add_history(line);
			c = parse(line, envp, &info);
			free(line);
			free_cmd(c, NO_ENV, &info);
		}
		else
		{
			free_split(info.env);
			return (1);
		}
		i++;
	}
	return (0);
}
