
#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	//t_cmd	*c;
	//struct sigaction	sig;

	//c = (t_cmd *){0};
	//sigemptyset(&sig.sa_mask);
	//init_signals(&sig);
	char *line;
	char	prompt[4097];

	//while (1)
	//{
		line = readline(get_prompt(prompt));
		cd(NULL, envp);
		line = readline(get_prompt(prompt));
		cd("~/COMMON_CORE/", envp);
		line = readline(get_prompt(prompt));
	//	c = parse(line);
		//exec(c, envp);
	//}
	return (0);
}
