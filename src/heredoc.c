
#include "../includes/minishell.h"

static void	putline_fd(char *s, int fd)
{
	while(*s)
		write(fd, s++, 1);
	write(fd, "\n", 1);
}

char	*heredoc(char *s)
{
	char	key[4096];
	char	*line;
	int	i;
	int fd;

	ft_memset(key, 0, 4096);
	i = 0;
	while(*s == ' ')
		s++;
	while ( *s && *s != ' ')
		key[i++] = *s++;
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
	// unlink("heredoc"); pour supprimer le fichier dnas l'exec
	return ("heredoc");
}

char	*no_heredoc(char *s)
{
	char	*file;
	int	i;

	file = NULL;
	i = 0;
	while(*s == ' ')
		s++;
	while ( *s && *s != ' ')
		file[i++] = *s++;
	return (file);
}
