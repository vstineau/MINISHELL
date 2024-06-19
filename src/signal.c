
#include "../includes/minishell.h"

//CTRL + 'C'
static void	handle_sigint()
{
	rl_redisplay();
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
	{
		g_signal_received = SIGINT;
		handle_sigint();
	}
	else if (signum == SIGQUIT)
	{
		g_signal_received = SIGQUIT;
		handle_sigquit();
	}
}

int	init_signals(struct sigaction *sa)
{
	sa->sa_sigaction = signal_handler;
	sa->sa_flags = SA_SIGINFO;
	if (sigaction(SIGINT, sa, NULL) == -1)
		return (0);
	if (sigaction(SIGQUIT, sa, NULL) == -1)
		return (0);
	return (1);
}
