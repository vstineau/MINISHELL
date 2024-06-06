`typedef enum`
`{`
	`PIPE = 0,`
	`CMD`
`}				t_token;`

`typedef enum`
`{`
	`APPEND = 0,`
	`NO_APPEND,`
	`HEREDOC,`
	`NO_HEREDOC,`
	`WIDE`
`}				t_redirect;`

`typedef struct s_cmd`
`{`
	`char	*cmd;`
	`char	*infile;`
	`char	*heredoc;`
	`char	*outfile;`
	`char	**arg;`
	`t_token	pipe;`
	`t_redirect	type;`
	`struct s_cmd	*next;`
	`struct s_cmd	*first;`
`}`						t_cmd;