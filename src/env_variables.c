/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstineau <vstineau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:53:59 by vstineau          #+#    #+#             */
/*   Updated: 2024/08/09 14:57:48 by vstineau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	utils_env1(char *s, t_iterator *a, int j)
{
	while (s[j] && !check_char(s[j], " \t"))
		j++;
	a->i += j - a->i;
	return (0);
}

static int	utils_env2(char *var, int len_var, t_iterator *a, int j)
{
	a->i += j - a->i;
	free(var);
	return (len_var);
}

static void	fill_key(char key[4096], char *s, int *j, t_iterator *a)
{
	while (s[*j] && !check_char(s[*j], " $\t/") && is_uppercase(s[*j]))
	{
		key[*j - a->i - 1] = s[*j];
		*j += 1;
	}
	if (s[*j] && !check_char(s[*j], "$\"= \t/"))
		key[*j - a->i - 2] = 4;
	if (s[*j] && s[*j] == '$' && (!s[*j + 1] || check_char(s[*j + 1], "\" \t")))
		a->dols_end = true;
	key[*j - a->i - 1] = '=';
}

char	*get_env_variable(char *var, char **envp, char *h, t_minishell *info)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		if (envp[i][j] == var[j])
		{
			while (envp[i][j] == var[j])
				j++;
			if (envp[i][j] && envp[i][j - 1] == var[j - 1] && var[j - 1] == '=')
			{
				h = ft_calloc(ft_strlen(envp[i] + j) + 1, 1);
				if (!h)
					exit_free_perror(NULL, ENV, info,
						BG_RED"memory allocation failed during parsing"RESET);
				ft_strcpy(h, envp[i] + j);
				return (h);
			}
		}
		i++;
	}
	free(h);
	return (NULL);
}

int	expand_env_v(char *s, char **line, t_minishell *info, t_iterator *a)
{
	int		j;
	char	key[4096];
	char	*var;
	int		len_line;

	len_line = ft_strlen(*line);
	if (len_line < ft_strlen(s))
		len_line = ft_strlen(s);
	j = 1 + a->i;
	var = NULL;
	ft_memset(key, 0, 4096);
	fill_key(key, s, &j, a);
	var = get_env_variable(key, info->env, NULL, info);
	if (!var)
		return (utils_env1(s, a, j));
	else
	{
		*line = ft_realloc(*line, len_line, len_line + ft_strlen(var) + 1);
		if (*line == NULL)
			exit_free_perror(NULL, ENV, info,
				BG_RED"memory allocation failed during parsing"RESET);
		ft_memcpy(*line + a->j, var, ft_strlen(var));
	}
	return (utils_env2(var, ft_strlen(var), a, j));
}
