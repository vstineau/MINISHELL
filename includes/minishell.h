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

extern int	g_signal_received;

typedef struct s_iterator
{
	int		i;
	int		j;
	bool	single_quotes;
	bool	doubles_quotes;
}		t_iterator;

typedef enum s_token
{
	CMD = 0,
	PIPE
}				t_token;

typedef enum s_redirect
{
	APPEND,
	NO_APPEND,
	HEREDOC,
	NO_HEREDOC ,
	WIDE
}				t_redirect;

typedef struct s_minishell
{
	int					code_error;
	char				**env;
	struct sigaction	sig;
}				t_minishell;

typedef struct s_cmd
{
	char				*cmd;
	char				*infile;
	char				*outfile;
	char				*path;
	char				**arg;
	int					fd;
	int					fd_h;
	t_token				pipe;
	int					error;
	int					previous_pipe;
	t_redirect			redirect;
	t_minishell			*i;
	struct s_cmd		*next;
}						t_cmd;
//----------UTILS----------------------//
char		*ft_itoa(int n);
char		**ft_split(char const *s, char c);
void		*ft_calloc(size_t nmemb, size_t size);
void		*ft_realloc(void *old, size_t old_length, size_t new_length);
void		*ft_memset(void *s, int c, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
int			ft_strlen(char *s);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strcpy(char *dest, char *src);
char		*ft_strncpy(char *dest, char *src, int n);
size_t		count_words(char const *s, char c);
char		*ft_strdup(char *s);
void		ft_sort_strings(int num, char **s);
int			ft_strncmp( const char *first, const char *second, size_t length);
int			env_size(char **envp);
char		*ft_strjoin(char const *s1, char const *s2);
void		ft_close(int pip[2], int infile);
char		*ft_strchr(const char *s, int c);
int			check_infile(char *file);
int			exit_close(int pip[2]);
int			count_arg(char *s);
char		*ft_strjoin_free(char *s1, char *s2);
char		*get_prompt(char *prompt, t_minishell *info, t_cmd *c);
int			check_char(char c, char *s);
int			is_uppercase(char c);
int			perror_and_return_i(t_minishell *info, char *s, int i);
//----------EXPAND----------------------//
char		*expand(char *s, t_minishell *info);
int			tilde(char *s, char **line, t_minishell *info, t_iterator *a);
int			expand_env_v(char *s, char **line,
				t_minishell *info, t_iterator *a);
void		no_expand_heredoc(char *s, char *line, t_iterator *a);
int			expand_doubles_quotes(t_iterator *a, char *line);
int			expand_single_quotes(t_iterator *a, char *line);
int			expand_dols_qmark(char *s, char **line,
				t_minishell *info, t_iterator *a);
void		ft_putstr_fd(char *s, int fd);
//----------PARSING----------------------//
char		**get_env(char **envp, char **argv, int argc);
t_cmd		*parse(char *line, t_minishell *info);
int			infile(char *s, t_cmd *c, t_minishell *info);
int			outfile(char *s, t_cmd *c, t_minishell *info);
int			heredoc(char *s, t_cmd *c, t_minishell *info, char *s1);
char		*fill_heredoc(char *line, int fd);
char		*fill_heredoc2(char *line, t_cmd *c, char *s1, t_minishell *info);
int			no_heredoc(char *s, t_cmd *c, t_minishell *info);
int			single_quotes(char *s, t_cmd *c, int i, int k);
int			double_quotes(char *s, t_cmd *c, char **envp, int *i);
int			env_variables(char *s, char **envp, t_cmd *c, int i);
char		*get_env_variable(char *var,
				char **envp, char *h, t_minishell *info);
int			get_cmd(char *s, t_cmd *c, int *i_arg, t_minishell *info);
//----------SIGNALS----------------------//
int			init_signals(t_minishell *info);
void		check_signal(t_minishell *info);
void		handle_sigquit(int signum, siginfo_t *info, void *context);
//-------------FREE----------------------//
void		exit_free_perror(t_cmd *c, bool env,
				t_minishell *info, char *error);
void		free_cmd(t_cmd *cmd, bool env, t_minishell *info);
void		free_split(char **split);
void		free_split_exit(char **split);
char		*free_return(char **cmd, char *endfile);
void		free_alls(char *path, char **cmd);
//----------EXECUTION--------------------//
char		*find_path(char **env, char *av);
char		**find_cmd(char *av);
char		*return_path(char **cmd, char *endfile, char *path);
void		apply_exec_middle_bonus(int fd, int pip[2], char **env, t_cmd *c);
void		exec_builtin(t_cmd *c, t_minishell *info, int fd, int pip[2]);
void		exec(t_minishell *info, t_cmd *c);
int			is_builtin(t_cmd *c);
char		*get_first_av(char *av);
char		**ft_print_export(char **env, int fd);
int			ft_isalpha(int c);
int			ft_isalnum(int c);
void		*wrong_identifier(char *av);
int			arg_ok_for_export(char *av);
//----------BUILTINS---------------------//
void		cd(char *path, char **envp, t_minishell *info);
void		pwd(int fd);
void		echo(char **av, int fd);
void		our_env(char **env, int fd);
void		our_exit(t_cmd *c, t_minishell *info);
char		**our_export(char **av, char **env, int fd);
char		**unset(char **av, char **env);

#endif
