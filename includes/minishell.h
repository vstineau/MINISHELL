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
# define ENV 1
# define NO_ENV 0

extern int g_signal_received;

typedef struct s_iterator
{
	int	i;
	int	j;
	bool	single_quotes;
	bool	doubles_quotes;
}		t_iterator;

typedef enum
{
	CMD = 0,
	PIPE
}				t_token;

typedef enum
{
	APPEND,
	NO_APPEND,
	HEREDOC,
	NO_HEREDOC ,
	WIDE
}				t_redirect;

typedef struct s_minishell
{
	int	code_error;
	char **env;
	struct sigaction sig;
}				t_minishell;

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
void	*ft_realloc(void *old, size_t old_length, size_t new_length);
char	*ft_strdup(char *s);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_strlen(char *s);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strncpy(char *dest, char *src, int n);
size_t	count_words(char const *s, char c);
int	count_arg(char *s);
char	*ft_strjoin_free(char *s1, char *s2);
char	*get_prompt(char *prompt, t_minishell *info, t_cmd *c);
int	check_char(char c, char *s);
int	is_uppercase(char c);
//----------EXPAND----------------------//
char	*expand(char *s, t_minishell *info);
int	tilde(char *s, char **line, t_minishell *info, t_iterator *a);
int	expand_env_v(char *s, char **line, t_minishell *info, t_iterator *a);
void	no_expand_heredoc(char *s, char *line, t_iterator *a);
int	expand_doubles_quotes(t_iterator *a, char *line);
int	expand_single_quotes(t_iterator *a, char *line);
//----------PARSING----------------------//
char	**get_env(char **envp);
t_cmd	*parse(char *line, t_minishell *info);
int	infile(char *s, t_cmd *c, t_minishell *info);
int	outfile(char *s, t_cmd *c, t_minishell *info);
int	heredoc(char *s, t_cmd *c, t_minishell *info);
int	no_heredoc(char *s, t_cmd *c, t_minishell *info);
int	single_quotes(char *s, t_cmd *c, int i, int k);
int	double_quotes(char *s, t_cmd *c,char **envp, int *i);
int	env_variables(char *s, char **envp, t_cmd *c, int i);
char *get_env_variable(char *var, char **envp, char *h, t_minishell *info);
int	get_cmd(char *s, t_cmd *c, int *i_arg, t_minishell *info);
//----------SIGNALS----------------------//
int	init_signals(t_minishell *info);
void	check_signal(t_minishell *info);
//-------------FREE----------------------//
void exit_free_perror(t_cmd *c, bool env, t_minishell *info, char *error);
void	free_cmd(t_cmd *cmd, bool env, t_minishell *info);
void	free_split(char **split);
//----------EXECUTION--------------------//
void exec(t_cmd *c, char **envp);
//----------BUILTINS---------------------//
void	pwd(void);
void	cd(char *path, char **envp, t_minishell *info);

#endif

