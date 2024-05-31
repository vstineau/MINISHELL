
#include "../includes/minishell.h"

int main()
{
	struct sigaction	sig;
	sigemptyset(&sig.sa_mask);
	init_signals(&sig);
	char *line;
	char	*prompt = ""B_BLUE"\u279C "B_WHITE" mini"B_RED"shell "RESET"";
	while (1)
	{
		line = readline(prompt);
			//parse(line);
		rl_on_new_line();
	}
	return (0);
}
