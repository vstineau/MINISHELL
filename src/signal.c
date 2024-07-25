
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

/*extern int rl_done = Flag to indicate that readline
 * has finished with the current input
   line and should return it. */
static void	test(void)
{
	return ;
}

//CTRL + '\'
void	handle_sigquit(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	(void)signum;
	write(2, "Quit (core dumped)\n", 20);
	g_signal_received = SIGQUIT;
	rl_done = true;
	unlink("heredoc");
}

//int	init_sigint(t_minishell *info)
//{
//	info->sa_sigaction = handle_sigquit;
//	if (sigaction(SIGQUIT, &info->sig, NULL) == -1)
//		return (0);
//	return (1);
//}
void	check_signal(t_minishell *info)
{
	if (g_signal_received == SIGINT || g_signal_received == SIGQUIT)
		info->code_error = 130;
	else if (g_signal_received == SIGQUIT)
		info->code_error = 131;
	else
		return ;
}

int	init_signals(t_minishell *info)
{
	sigemptyset(&info->sig.sa_mask);
	info->sig.sa_sigaction = handle_sigint;
	info->sig.sa_flags = SA_SIGINFO;
	rl_event_hook = (void *)test;
	if (sigaction(SIGINT, &info->sig, NULL) == -1)
		return (0);
	info->sig.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &info->sig, NULL) == -1)
		return (0);
	return (1);
}
