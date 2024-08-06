
#include "../includes/minishell.h"

int	g_signal_received;

static int	is_blank(char *s)
{
	int	i;

	if (!s)
		return (1);
	i = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

//void	printlist(t_cmd *cmd)
//{
//	t_cmd	*current;
//	int		i = 0;
//
//	current = cmd;
//	while (current)
//	{
//		int j = 0;
//		printf(BHI_CYAN"cmd nb %d = %s\n"RESET, i, current->cmd);
//		printf(BHI_GREEN"infile nb %d = %s\n"RESET, i, current->infile);
//		printf(BHI_MAGENTA"outfile nb %d = %s\n"RESET, i, current->outfile);
//		printf(BHI_RED"pipe %d\n"RESET, current->pipe);
//		printf(B_GREEN"fd %d\n"RESET, current->fd);
//		printf(B_BLUE"fd_h %d\n"RESET, current->fd_h);
//		printf(B_RED"error %d\n"RESET, current->error);
//		while (current->arg[j] && current->arg[j][0] != '\0')
//		{
//			printf(BHI_YELLOW"arg[%d] = %s\n"RESET, j, current->arg[j]);
//			j++;
//		}
//		printf(BHI_BLUE" ---------------------------- \n"RESET);
//		i++;
//		current = current->next;
//	}
//}
//
static void	unwanted_argc(int argc)
{
	if (argc > 1)
		exit(1);
}

static void	signals_stuff(t_minishell *info)
{
	check_signal(info);
	init_signals(info);
}

static void	check_unwanted_char(char *line, char *s, t_cmd *c)
{
	if (!line)
		return ;
	free(line);
	if (!c->cmd && !c->outfile && !c->infile)
	{
		if (c->next && c->next->pipe == PIPE)
			set_error_code(c, 2);
	}
	if (!s)
		return ;
	check_unwanted_char_cmd(c);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	info;
	t_cmd		*c;
	char		*line;
	char		prompt[4097];

	unwanted_argc(argc);
	c = (t_cmd *){0};
	info = (t_minishell){0};
	info.env = get_env(envp, argv, argc);
	while (1)
	{
		signals_stuff(&info);
		line = readline(get_prompt(prompt, &info, c));
		if (!line)
			free_split_exit(info.env);
		add_history(line);
		line = expand(line, &info);
		c = parse(line, &info);
		check_unwanted_char(line, c->cmd, c);
		if (check_error(c))
			perror(BG_RED"parsing error"RESET);
		if ((!is_blank(c->cmd) && !check_error(c)) || !is_blank(c->outfile))
			exec(&info, c);
		free_cmd(c, NO_ENV, &info);
	}
}
