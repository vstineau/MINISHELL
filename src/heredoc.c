
#include "../includes/minishell.h"

static void	putline_fd(char *s, int fd)
{
	while(*s)
		write(fd, s++, 1);
	write(fd, "\n", 1);
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
	while(s[i] == ' ')
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

	c->infile = ft_calloc(ft_strlen(s) + 1, 1);
	if (!c->infile)
		{
			perror(BG_RED"memory allocation failed during parsing"RESET);
			free_cmd(c, ENV, info);
			exit(1);
		}
	i = 0;
	j = 0;
	while(s[i] == ' ')
		i++;
	while (s[i] && s[i] != ' ')
		c->infile[j++] = s[i++];
	return (i);
}
