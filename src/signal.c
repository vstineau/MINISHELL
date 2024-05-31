
#include "../includes/minishell.h"

//CTRL + 'C'
static void	handle_sigint()
{
	rl_redisplay();
	//if (//interactive mode)
	//{
	//	display_prompt();
	//	return ;
	//}
	//else
	//{
	//	//kill le process en cour +
	//	display_prompt();
	//	return ;
	//}

}

//CTRL + '\'
static void	handle_sigquit()
{
}

static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signum == SIGINT)
		handle_sigint();
	else if (signum == SIGQUIT)
		handle_sigquit();
}

int	init_signals(struct sigaction *sa)
{
	sa->sa_sigaction = signal_handler;
	if (sigaction(SIGINT, sa, NULL) == -1)
		return (0);
	if (sigaction(SIGQUIT, sa, NULL) == -1)
		return (0);
	return (1);

}
