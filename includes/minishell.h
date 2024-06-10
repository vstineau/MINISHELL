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

typedef enum
{
	PIPE = 0,
	CMD
}				t_token;

typedef enum
{
	APPEND = 0,
	NO_APPEND,
	HEREDOC,
	NO_HEREDOC,
	WIDE
}				t_redirect;

typedef struct s_cmd
{
	char	*cmd;
	char	*infile;
	char	*heredoc;
	char	*outfile;
	char	**arg;
	t_token	pipe;
	t_redirect	redirect;
	struct s_cmd	*next;
}						t_cmd;

//------------UTILS----------------------//
char	**ft_split(char const *s, char c);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memset(void *s, int c, size_t n);
int		ft_strlen(char *s);
char *get_prompt(char *prompt);
char	*ft_strcpy(char *dest, char *src);
size_t	count_words(char const *s, char c);
//----------PARSING----------------------//
int	init_signals(struct sigaction *sa);
t_cmd	*parse(char *line);
void	infile(char *s, t_cmd **c);
void	outfile(char *s, t_cmd **c);
//-------------FREE----------------------//
void	free_split(char **split);
//----------EXECUTION--------------------//
void exec(t_cmd *c, char **envp);
//----------BUILTINS---------------------//
void cd(char *path, char **envp);

#endif

