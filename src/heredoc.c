
#include "../includes/minishell.h"

void	no_expand_heredoc(char *s, char *line, t_iterator *a)
{
	int	i;

	i = 0;
	while ((s + a->i)[i] && check_char((s + a->i)[i], " \t"))
	{
		(line + a->j)[i] = (s + a->i)[i];
	}
	a->i += i;
	a->j += i;
}

static void	putline_fd(char *s, int fd)
{
	while(*s)
		write(fd, s++, 1);
	write(fd, "\n", 1);
}

static int	no_heredoc2(char *s, t_cmd *c, t_minishell *info)
{
	char	key[4096];
	int	i = 1;
	
	ft_memset(key, 0, 4096);
	if (*s == '$')
	{
		while (s[i] && check_char(s[i], " \t"))
		{
			key[i - 1] = s[i];
			i++;
		}
		key[i - 1] = '=';
		c->infile = ft_strjoin_free(c->infile, get_env_variable(key, info->env));
	}
	else if (*s == '<')
		i += infile(s, c, info);
	else if (*s == '>')
		i += outfile(s, c);
	return (i);
}

int	heredoc(char *s, t_cmd *c, t_minishell *info)
{
	char	key[4096];
	char	*line;
	int	i;
	int	j;
	int fd;

	ft_memset(key, 0, 4096);
	i = 0;
	j = 0;
	while(!check_char(s[i], "~ \t|><$"))
		i++;
	if (!s[i])
	{
		perror(BG_RED"syntax error"RESET);
		return (i);
	}
	while ( s[i] && s[i] != ' ')
		key[j++] = s[i++];
	line = readline(BHI_BLACK"> "RESET);
	if (!line)
	{
		free_cmd(c, ENV, info);
		exit(1);
	}
	open("heredoc", O_CREAT, S_IRWXU);
	fd = open("heredoc", O_WRONLY);
	while (ft_strcmp(key, line) && g_signal_received != SIGINT)
	{
		putline_fd(line, fd);
		free(line);
		line = readline(BHI_BLACK"> "RESET);
		if (!line)
		{
			free_cmd(c, ENV, info);
			exit(1);
		}
	}
	free(line);
	c->infile = "heredoc";
	return (i);
}

int	no_heredoc(char *s, t_cmd *c, t_minishell *info)
{
	int	i;
	int	j;

	if (c->infile)
		free(c->infile);
	c->infile = ft_calloc(ft_strlen(s) + 1, 1);
	if (!c->infile)
		{
			perror(BG_RED"memory allocation failed during parsing"RESET);
			free_cmd(c, ENV, info);
			exit(1);
		}
	i = 0;
	j = 0;
	while(!check_char(s[i], "  \t"))
		i++;
	while(s[i]  && !check_char(s[i], "  \t|><$"))
		c->infile[j++] = s[i++];
	return (i + no_heredoc2(s, c, info));
}

