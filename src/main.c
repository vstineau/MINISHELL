
#include "../includes/minishell.h"

int g_signal_received;

void	printlist(t_cmd *cmd)
{
	t_cmd *current;
	int i = 0;

	current = cmd;
	while (current)
	{
		int j = 0;
		printf(BHI_CYAN"cmd nb %d = %s\n"RESET, i, current->cmd);
		printf(BHI_GREEN"infile nb %d = %s\n"RESET, i, current->infile);
		printf(BHI_MAGENTA"outfile nb %d = %s\n"RESET, i, current->outfile);
		printf(BHI_RED"pipe %d\n"RESET, current->pipe);
		while (current->arg[j] && current->arg[j][0] != '\0')
		{
			printf(BHI_YELLOW"arg[%d] = %s\n"RESET, j, current->arg[j]);
			j++;
		}
		printf(BHI_BLUE" ---------------------------- \n"RESET);
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
	char *line;
	char	prompt[4097];

	c = (t_cmd *){0};
	info = (t_minishell){0};
	info.env = get_env(envp);
	while (1)
	{
		init_signals(&info);
		check_signal(&info);
		line = readline(get_prompt(prompt, &info, c));
		if (line)
		{
			add_history(line);
			line = expand(line, &info);
			g_signal_received = 0;
			c = parse(line, &info);
			free(line);
			exec(&info, c);
	//		printlist(c);
			free_cmd(c, NO_ENV, &info);
		}
		else
		{
			free_split(info.env);
			return (1);
		}
	}
	return (0);
}
