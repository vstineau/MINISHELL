
#include "../includes/minishell.h"

static void	putline_fd(char *s, int fd)
{
	while(*s)
		write(fd, s++, 1);
	write(fd, "\n", 1);
}

int	heredoc(char *s, t_cmd *c)
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
	while ( s[i] && s[i] != ' ')
		key[j++] = s[i++];
	line = readline(BHI_BLACK"> "RESET);
	open("heredoc", O_CREAT, S_IRWXU);
	fd = open("heredoc", O_WRONLY);
	while (ft_strcmp(key, line))
	{
		putline_fd(line, fd);
		free(line);
		line = readline(BHI_BLACK"> "RESET);
	}
	free(line);
	c->infile = "heredoc";
	// unlink("heredoc"); pour supprimer le fichier dnas l'exec
	return (i);
}

int	no_heredoc(char *s, t_cmd *c)
{
	int	i;
	int	j;

	c->infile = ft_calloc(ft_strlen(s) + 1, 1);
	if (!c->infile)
		return (0); // print error et exit
	i = 0;
	j = 0;
	while(s[i] == ' ')
		i++;
	while (s[i] && s[i] != ' ')
		c->infile[j++] = s[i++];
	return (i);
}
