/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstineau <vstineau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:23:06 by vstineau          #+#    #+#             */
/*   Updated: 2024/05/22 12:06:12 by vstineau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//CTRL + 'C'
static void	handle_sigint()
{
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

int	init_signals(struct sigaction sa)
{
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = signal_handler;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (0);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		return (0);
	if (sigaction(SIGKILL, &sa, NULL) == -1)
		return (0);
	return (1);

}
