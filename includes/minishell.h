#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stddef.h>
# include <signal.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "color.h"

static int g_signal_received;

typedef struct s_cmd
{
	char	*cmd;
	char	*infile;
	char	*outfile;
	char	**arg;
	bool	pipe;
	struct s_cmd	*next;
}						t_cmd;


//----------UTILS----------------------//
char	**ft_split(char const *s, char c);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memset(void *s, int c, size_t n);
;
char	*ft_strcpy(char *dest, char *src);
//----------PARSING--------------------//
int	init_signals(struct sigaction *sa);
t_cmd	*parse(char *line);
//----------FREE_______________________//
void	free_split(char **split);
#endif

