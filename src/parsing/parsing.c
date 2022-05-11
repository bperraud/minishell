/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 19:29:26 by jboumal           #+#    #+#             */
/*   Updated: 2022/04/12 19:33:29 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_quotes_and_parenthesis(t_cmd *cmd, t_split *split, char *s)
{
	if ((*s == '\'' || *s == '\"')
		&& (split->quote == *s || !split->quote) && !split->par)
	{
		if (!split->quote)
			split->quote = *s;
		else
			split->quote = '\0';
		s++;
	}
	else if (!split->quote && *s == '(')
	{
		if (!split->par)
		{
			cmd->cmd = add_string(cmd->cmd, split->word);
			split->word = NULL;
		}
		split->par ++;
	}
	else if (!split->quote && *s == ')')
	{
		split->word = add_char(split->word, *s);
		split->par --;
	}
	return (s);
}

static char	*replace_env_var(char *s, char **env)
{
	char	*s2;
	char	*var;
	int		i;
	bool	squote;

	s2 = NULL;
	i = 0;
	squote = false;
	while (s[i])
	{
		if (!squote && s[i] != '$')
			s2 = add_char(s2, s[i]);
		else if (s[i] == '\'')
			squote = (squote + 1) % 2;
		else
		{
			var = ft_strndup(s + i + 1, get_var_len(s + i + 1));
			i += get_var_len(s + i + 1);
			s2 = add_multiple_chars(s2, ft_getenv(var, env));
			free(var);
		}
		i++;
	}
	free(s);
	return (s2);
}

static char	*free_and_dup(t_split *split, char *s_ini, char *s)
{
	free(split);
	if (s)
		s = ft_strndup(s, ft_strlen(s));
	free(s_ini);
	return (s);
}

static char	*handle_special(t_cmd *cmd, t_split *split, char *s_ini, char *s)
{
	char	*t;

	t = handle_in_redirections(cmd, split, s);
	if (!t)
		return (free_and_dup(split, s_ini, NULL));
	t = handle_out_redirections(cmd, split, t);
	if (!t)
		return (free_and_dup(split, s_ini, NULL));
	if (t == s)
	{
		t = handle_quotes_and_parenthesis(cmd, split, s);
		if (t == s)
			cmd_list_add_char(cmd, split, s);
		s++;
	}
	else
		s = t;
	return (s);
}

char	*get_next_cmd(char *s, char **env, t_cmd *cmd)
{
	t_split	*split;
	char	*s_ini;

	split = init_split();
	s = replace_env_var(s, env);
	s_ini = s;
	while (s && *s && (split->quote || split->par || !ft_strchr("&|", *s)))
	{
		s = handle_special(cmd, split, s_ini, s);
		if (!s)
			return (NULL);
	}
	cmd->cmd = add_string(cmd->cmd, split->word);
	if (s)
		s = handle_operator(cmd, s);
	return (free_and_dup(split, s_ini, s));
}
