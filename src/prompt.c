
#include "../includes/minishell.h"

char *get_prompt(char *prompt)
{
	int i;

//	ft_memset(prompt, 0, 4097);
	getcwd(prompt, 4097);
	i = ft_strlen(prompt);
	ft_strcpy(prompt + i, BHI_GREEN"\001\u279C\002 "RESET);
	return (prompt);
}
