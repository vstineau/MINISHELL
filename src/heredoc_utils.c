
#include "../includes/minishell.h"

int	perror_and_return_i(char *s, int i)
{
	perror(s);
	return (i);
}

static void	putline_fd(char *s, int fd)
{
	while (*s)
		write(fd, s++, 1);
	write(fd, "\n", 1);
}

char	*fill_heredoc(char *line, t_cmd *c, int fd, t_minishell *info)
{
	putline_fd(line, fd);
	free(line);
	line = readline(BHI_BLACK"> "RESET);
	if (!line)
		exit_free_perror(c, ENV, info, NULL);
	return (line);
}
