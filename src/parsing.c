
#include "../includes/minishell.h"

t_cmd	*ft_lstnew(char *s)
{
	t_cmd *new_cmd;

	new_cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!new_cmd)
		return (NULL);// exit error
	new_cmd->arg = ft_calloc(count_words(s, ' ') * sizeof(char *),1);
	if (!new_cmd->arg)
		return (NULL);// exit error
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

static int	get_cmd(char *s, t_cmd *c, int *i_arg)
{
	int i;

	i = 0;
	if (c->cmd)
	{
		while (s[i] && s[i] != ' ')
			i++;
		c->cmd = ft_calloc(i + 1, 1);
		if (!c->arg)
			return (0); // error et exit
		i = 0;
		while (s[i] && s[i] != ' ')
		{
			c->cmd[i] = s[i];
			i++;
		}
		return (i);
	}
	else
	{
		while (s[i] && s[i] != ' ')
			i++;
		c->arg[*i_arg] = ft_calloc(i + 1, 1);
		if (!c->arg)
			return (0); // error et exit
		i = 0;
		while (s[i] && s[i] != ' ')
		{
			c->arg[*i_arg][i] = s[i];
			i++;
		}
		return (i);
	}
}

t_cmd	*parse(char *s, char **envp)
{
	t_cmd *c;
	t_cmd *current;
	int	i_arg;

	i_arg = 0;
	c = ft_lstnew(s);
	current = c;
	while (*s != '\0')
	{
		if (*s == '<')
			s += infile(s, c);
		else if (*s == '>')
			s += outfile(s, c);
		else if (*s == '$')
		{
			write(1, "ok\n", 3);
			s += env_variables(s, envp, c, i_arg++);
		}
		else if (*s == '"')
			;
		else if (*s == '\'')
			s += single_quotes(s, c, i_arg++);
		else if (*s == '|')
		{
			ft_lstadd_back(&c, ft_lstnew(s));
			current = current->next;
		}
		else
			s += get_cmd(s, c, &i_arg);
		printf("line = %s\n", s);
	}
	return (c);
}
