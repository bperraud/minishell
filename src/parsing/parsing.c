/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 19:29:26 by jboumal           #+#    #+#             */
/*   Updated: 2022/06/01 16:51:23 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_quotes_and_parenthesis(t_cmd *cmd, t_split *sp, char *s)
{
	if (ft_strchr("\"\'", *s) && (sp->quote == *s || !sp->quote) && !sp->par)
	{
		if (!sp->quote)
			sp->quote = *s;
		else
			sp->quote = '\0';
		sp->word = add_char(sp->word, *s);
		s++;
	}
	else if (!sp->quote && *s == '(')
	{
		if (!sp->par)
		{
			cmd->cmd = add_string(cmd->cmd, sp->word);
			sp->word = NULL;
		}
		sp->par ++;
	}
	else if (!sp->quote && *s == ')')
	{
		sp->word = add_char(sp->word, *s);
		sp->par --;
		s++;
	}
	return (s);
}

static char	*replace_env_var(char *s, char **env, int i, char quote)
{
	char	*s1;
	char	*s2;
	char	*var;

	s1 = NULL;
	while (s[++i])
	{
		if ((s[i] == '\'' || s[i] == '\"') && (quote == s[i] || !quote))
			quote = change_quote(quote, s[i]);
		else if (quote != '\'' && s[i] == '$' && s[i + 1] != '.')
		{
			var = ft_strndup(s + i + 1, get_var_len(s + i + 1));
			i += get_var_len(s + i + 1);
			s2 = ft_getenv(var, env);
			s1 = add_multiple_chars(s1, s2);
			free(s2);
			free(var);
		}
		else
			s1 = add_char(s1, s[i]);
	}
	free(s);
	return (s1);
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
	int		i;

	i = -1;
	split = init_split();
	s_ini = s;
	while (s && *s && (split->quote || split->par || !ft_strchr("&|", *s)))
	{
		s = handle_special(cmd, split, s_ini, s);
		if (!s)
			return (NULL);
		if (split->quote && ft_strchr("&|", *s))
			split->word = add_char(split->word, *s);
	}
	cmd->cmd = add_string(cmd->cmd, split->word);
	if (s && !split->quote)
		s = handle_operator(cmd, s);
	handle_wildcards(cmd);
	if (cmd->cmd)
	{
		while (cmd->cmd[++i])
			cmd->cmd[i] = replace_env_var(cmd->cmd[i], env, -1, '\0');
	}
	return (free_and_dup(split, s_ini, s));
}
