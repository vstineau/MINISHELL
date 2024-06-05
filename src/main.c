
#include "../includes/minishell.h"

int main()
{
	t_cmd	*c;

	c = (t_cmd *){0};
	//struct sigaction	sig;
	//sigemptyset(&sig.sa_mask);
	//init_signals(&sig);
	char *line;
	char	*prompt = ""B_GREEN"\001\u279C\002 "BHI_BLUE" minishell"RESET"";
	while (1)
	{
		line = readline(prompt);
		c = parse(line);
	}
	return (0);
}
