/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstineau <vstineau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:54:10 by vstineau          #+#    #+#             */
/*   Updated: 2024/08/13 14:57:02 by aroualid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_midle(t_minishell *info, int fd, t_cmd *c, t_cmd *c_first)
{
	int		id;
	int		pip[2];

	c->i->write_error = 0;
	if (c->next == NULL && c->previous_pipe != 1 && (is_builtin(c) == 1))
		return (exec_first_case(c_first, c, fd, pip));
	if (is_builtin(c) == 0)
		c->path = find_path(info->env, c->cmd, info);
	if (pipe(pip) == -1)
		free_and_close (fd, pip, c_first, EXIT_FAILURE);
	id = fork();
	info->last_pid = id;
	if (id == -1)
		free_and_close (fd, pip, c_first, EXIT_FAILURE);
	if (id == 0)
	{
		close(pip[0]);
		c_first->close = 0;
		before_exec(c, c_first, fd, pip);
		free_and_close(fd, pip, c_first, info->code_error);
	}
	else
		info->code_error = 0;
	close_before(fd, pip, c_first);
	return (pip[0]);
}

void	init_void(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	(void)signum;
	g_signal_received = SIGINT;
	return ;
}

int	init_sigquit(t_minishell *info)
{
	ft_memset(&info->sig, 0, sizeof(sigaction));
	sigemptyset(&info->sig.sa_mask);
	info->sig.sa_sigaction = handle_sigquit;
	if (sigaction(SIGQUIT, &info->sig, NULL) == -1)
		return (0);
	info->sig.sa_sigaction = init_void;
	if (sigaction(SIGINT, &info->sig, NULL) == -1)
		return (0);
	return (1);
}

void	check_outfile(t_cmd *c)
{
	c->fd = open(c->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	close (c->fd);
}

void	exec(t_minishell *info, t_cmd *c)
{
	int		pipout;
	t_cmd	*temp;

	temp = c;
	pipout = 42;
	c->i->is_builtin = 0;
	if (init_sigquit(info) == 0)
		exit_free_perror(temp, ENV, info, "");
	if (check_dobble_pipe(temp, pipout) == 1)
		return ((void)
			ft_putstr_fd ("syntax error near unexpected token `|'\n", 2, c->i));
	while (temp)
	{
		if (temp->outfile != NULL && temp->cmd == NULL)
			check_outfile(temp);
		if (temp->cmd)
			pipout = exec_midle(info, pipout, temp, c);
		if (temp->pipe == PIPE)
			temp->next->previous_pipe = 1;
		temp = temp->next;
	}
	apply_wait(c, info);
	close(pipout);
}
