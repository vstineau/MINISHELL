
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

int	get_pipe(char *s, int *i, t_cmd **current, t_minishell *info)
{
	*i = 0;
	ft_lstadd_back(current, ft_lstnew(s, *current, info));
	*current = (*current)->next;
	(*current)->pipe = PIPE;
	ft_lstadd_back(current, ft_lstnew(s, *current, info));
	*current = (*current)->next;
	return (1);
}

t_cmd	*parse(char *s, char **envp, t_minishell *info)
{
	t_cmd *c;
	t_cmd *current;
	int	i_arg;

	g_signal_received = 0;
	if (!s)
		return (NULL);
	i_arg =0;
	c = NULL;
	c = ft_lstnew(s, c, info);
	current = c;
	while (*s != '\0')
	{
		while (*s == ' ')
			s++;
		printf(B_GREEN" *s  = %c\n"RESET, *s);
		if (*s == '<')
			s += infile(s, current, info);
		else if (*s == '>')
			s += outfile(s, current);
		else if (*s == '$')
			s += env_variables(s, envp, current, i_arg++);
		else if (*s == '"')
			s += double_quotes(s, current, envp, &i_arg);
		else if (*s == '\'')
			s += single_quotes(s, current, i_arg++);
		else if (*s == '|')
		{
			s += get_pipe(s, &i_arg, &current, info);
		}
		else
		{
			printf(B_YELLOW"i[%d]\n"RESET, i_arg);
			s += get_cmd(s, current, &i_arg);
		}
	}
	return (c);
}
