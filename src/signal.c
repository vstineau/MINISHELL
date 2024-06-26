
#include "../includes/minishell.h"
#include <readline/readline.h>

//CTRL + 'C'
static void	handle_sigint(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	(void)signum;
	g_signal_received = SIGINT;
	rl_done = true;
	unlink("heredoc");
}
/*extern int rl_done = Flag to indicate that readline has finished with the current input
   line and should return it. */
static void	test()
{
	return;
}

//CTRL + '\'
//static void	handle_sigquit(int signum, siginfo_t *info, void *context)
//{
//	(void)info;
//	(void)context;
//	(void)signum;
//	write(2, "Quit (core dumped)\n", 20);
//	g_signal_received = SIGQUIT;
//}
//
void	check_signal(t_minishell *info)
{
	if (g_signal_received == SIGINT || g_signal_received == SIGQUIT)
		info->code_error = 130;
	else if (g_signal_received == SIGQUIT)
		info->code_error = 131;
	else
		return ;
}

int	init_signals(struct sigaction *sa)
{
	sa->sa_sigaction = handle_sigint;
	sa->sa_flags = SA_SIGINFO;
	rl_event_hook = (void *)test;
	if (sigaction(SIGINT, sa, NULL) == -1)
		return (0);
	//sa->sa_sigaction = handle_sigquit;
	sa->sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, sa, NULL) == -1)
		return (0);
	return (1);
}
