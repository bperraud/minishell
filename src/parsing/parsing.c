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

static void	handle_quotes_and_parenthesis(t_cmd *cmd, t_split *split, char *s)
{
	if ((*s == '\'' || *s == '\"')
		&& (split->quote == *s || !split->quote) && !split->par)
	{
		if (!split->quote)
			split->quote = *s;
		else
			split->quote = '\0';
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
}

static char	*handle_in_redirections(t_cmd *cmd, t_split *split, char *s_orig)
{
	char	*s;

	s = s_orig;
	if (split->quote || split->par)
		return (s_orig);
	while (*s == ' ')
		s++;
	if (*s == '<' && *(s + 1) == '<')
	{
		s += 2;
		cmd->here_doc = split->word;
		split->word = NULL;
		return (s);
	}
	else if (*s == '<')
	{
		s++;
		while (*s == ' ')
			s++;
		cmd->infile = split->word;
		split->word = NULL;
		return (s);
	}
	return (s_orig);
}

static void	cmd_list_add(t_cmd *cmd, t_split *split, char *s)
{
	if (!ft_strchr("&|", *s))
	{
		if (split->par || split->quote || !ft_strchr(" )", *s))
			split->word = add_char(split->word, *s);
		else
		{
			cmd->cmd = add_string(cmd->cmd, split->word);
			split->word = NULL;
		}
	}
}

t_cmd	*sh_split(char *s)
{
	t_cmd	*cmd;
	t_split	*split;
	char	*t;

	split = init_split();
	cmd = init_cmd();
	while (*s)
	{
		t = handle_in_redirections(cmd, split, s);
		//t = handle_out_redirections(cmd, split, s);
		if (t == s)
		{
			handle_quotes_and_parenthesis(cmd, split, s);
			cmd_list_add(cmd, split, s);
			s++;
		}
		else
			s = t;
	}
	cmd->cmd = add_string(cmd->cmd, split->word);
	free(split);
	return (cmd);
}
