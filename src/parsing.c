
#include "../includes/minishell.h"

t_cmd	*ft_lstnew(char *s,t_cmd *c, t_minishell *info)
{
	t_cmd *new_cmd;
	
	new_cmd = NULL;
	new_cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!new_cmd)
	{
		free_cmd(c, ENV, info);
		perror(BG_RED"memory allocation failed during parsing"RESET);
		exit(1);
	}
	new_cmd->arg = NULL;
	new_cmd->arg = ft_calloc((count_words(s, ' ') + 1), sizeof(char *));
	if (!new_cmd->arg)
	{
		free_cmd(c, ENV, info);
		free(new_cmd);
		perror(BG_RED"memory allocation failed during parsing"RESET);
		exit(1);
	}
	s += 1;
	return (new_cmd);
}

void	ft_lstadd_back(t_cmd **cmd, t_cmd *new)
{
	t_cmd *current;
	t_cmd *previous;

	if (!new)
		return ;
	if (!*cmd)
	{
		*cmd = new;
		return ;
	}
	current = *cmd;
	while (current)
	{
		previous = current;
		current = current->next;
	}
	previous->next = new;
}

t_cmd	*parse(char *s, char **envp, t_minishell *info)
{
	t_cmd *c;
	t_cmd *current;
	int	i_arg;

	if (!s)
		return (NULL);
	i_arg =0;
	c = NULL;
	c = ft_lstnew(s, c, info);
	current = c;
	while (*s != '\0')
	{
		if (*s == '<')
			s += infile(s, c, info);
		else if (*s == '>')
			s += outfile(s, c);
		else if (*s == '$')
		{
			s += env_variables(s, envp, c, i_arg++);
		}
		else if (*s == '"')
			s += double_quotes(s, c, envp, &i_arg);
		else if (*s == '\'')
			s += single_quotes(s, c, i_arg++);
		else if (*s == '|')
		{
			ft_lstadd_back(&c, ft_lstnew(s, c, info));
			current = current->next;
		}
		else
		{
			s += get_cmd(s, c, &i_arg);
		}
	}
	return (c);
}
