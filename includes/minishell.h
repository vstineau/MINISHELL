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
# include <sys/stat.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "color.h"

//__int128

# define PATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"

static int g_signal_received;

typedef enum
{
	PIPE = 0,
	CMD
}				t_token;

typedef enum
{
	APPEND,
	NO_APPEND,
	HEREDOC,
	NO_HEREDOC ,
	WIDE
}				t_redirect;

typedef struct s_cmd
{
	char	*cmd;
	char	*infile;
	char	*outfile;
	char	*path;
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
int		ft_strcmp(char *s1, char *s2);
char	*get_prompt(char *prompt);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strncpy(char *dest, char *src, int n);
size_t	count_words(char const *s, char c);
char	*ft_strjoin_free(char *s1, char *s2);
//----------PARSING----------------------//
int	init_signals(struct sigaction *sa);
t_cmd	*parse(char *line, char **envp);
int	infile(char *s, t_cmd *c);
int	outfile(char *s, t_cmd *c);
int	heredoc(char *s, t_cmd *c);
int	no_heredoc(char *s, t_cmd *c);
int	single_quotes(char *s, t_cmd *c, int i);
int	double_quotes(char *s, t_cmd *c,char **envp, int *i);
int	env_variables(char *s, char **envp, t_cmd *c, int i);
char *get_env_variable(char *var, char **envp);
int	get_cmd(char *s, t_cmd *c, int *i_arg);
//-------------FREE----------------------//
void	free_split(char **split);
//----------EXECUTION--------------------//
void exec(t_cmd *c, char **envp);
//----------BUILTINS---------------------//
void	cd(char *path, char **envp);
void	pwd(void);

#endif

