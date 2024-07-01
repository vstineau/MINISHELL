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
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "color.h"
# include <stdint.h>

//__int128

# define PATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
# define ENV 1
# define NO_ENV 0

extern int g_signal_received;

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
	int		fd;
	t_token	pipe;
	t_redirect	redirect;
	struct s_cmd	*next;
}						t_cmd;

//------------UTILS----------------------//
char	**ft_split(char const *s, char c);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_realloc(void *old, size_t old_length, size_t new_length);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_strlen(char *s);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strncpy(char *dest, char *src, int n);
size_t	count_words(char const *s, char c);
char    *ft_strdup(char *s);
char	**get_env(char **envp);
void	ft_sort_strings(int num, char **s);
int		ft_strncmp( const char *first, const char *second, size_t length);
int		env_size(char **envp);
void	ft_bzero(void *s, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_close(int pip[2], int infile);
char	*ft_strchr(const char *s, int c);
int		check_infile(char *file);
int		exit_close(int pip[2]);
int	count_arg(char *s);
char	*ft_strjoin_free(char *s1, char *s2);
char	*get_prompt(char *prompt, t_minishell *info);
//----------PARSING----------------------//
char	**get_env(char **envp);
t_cmd	*parse(char *line, char **envp, t_minishell *info);
int	tilde(t_cmd *c, int i, t_minishell *info);
int	infile(char *s, t_cmd *c, t_minishell *info);
int	outfile(char *s, t_cmd *c);
int	heredoc(char *s, t_cmd *c, t_minishell *info);
int	no_heredoc(char *s, t_cmd *c, t_minishell *info);
int	single_quotes(char *s, t_cmd *c, int i);
int	double_quotes(char *s, t_cmd *c,char **envp, int *i);
int	env_variables(char *s, char **envp, t_cmd *c, int i);
char *get_env_variable(char *var, char **envp);
int	get_cmd(char *s, t_cmd *c, int *i_arg);
//----------SIGNALS----------------------//
int	init_signals(t_minishell *info);
void	check_signal(t_minishell *info);
//-------------FREE----------------------//
void	free_cmd(t_cmd *cmd, bool env, t_minishell *info);
void	free_split(char **split);
char	*free_return(char **cmd, char *endfile);
void	free_alls(char *path, char **cmd);
//----------EXECUTION--------------------//
char	*find_path(char **env, char *av);
char	**find_cmd(char *av);
char	*return_path(char **cmd, char *endfile, char *path);
void	apply_exec_first_bns(char *av, char **env, char *file, int pip[2]);
void	apply_exec_middle_bonus(int fd, int pip[2], char **env, char *av);
void	apply_exec_last_bns(char *av, char **env, int outfile, int fd);
//----------BUILTINS---------------------//
void	cd(char *path, char **envp);
void	pwd(void);
void	echo(char **av, int fd);
void	our_env(char **env);
void    our_exit(t_cmd *c, t_minishell *info);
char	**our_export(char **av, char **env);
char	**unset(char **av, char **env);

#endif

