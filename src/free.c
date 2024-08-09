/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstineau <vstineau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:55:01 by vstineau          #+#    #+#             */
/*   Updated: 2024/08/09 16:34:58 by vstineau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_cmd(t_cmd *cmd, bool env, t_minishell *info)
{
	t_cmd	*temp;

	if (env)
		free_split(info->env);
	while (cmd)
	{
		temp = cmd;
		if (cmd->fd_h != -1 && cmd->fd_h != 0)
			close(cmd->fd_h);
		if (cmd->path && (ft_strcmp(cmd->path, cmd->cmd)) != 0)
			free(cmd->path);
		if (cmd->cmd)
			free(cmd->cmd);
		if (cmd->infile && cmd->redirect != HEREDOC)
			free(cmd->infile);
		if (cmd->outfile)
			free(cmd->outfile);
		if (cmd->arg)
			free_split(cmd->arg);
		if (cmd->redirect == HEREDOC)
			unlink("heredoc");
		cmd = cmd->next;
		free(temp);
	}
	cmd = NULL;
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	free_split_exit(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	exit(1);
}

void	exit_free_perror(t_cmd *c, bool env, t_minishell *info, char *error)
{
	if (error)
		perror(error);
	free_cmd(c, env, info);
	exit(1);
}
