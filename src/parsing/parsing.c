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

static void	cmd_list_add_char(t_cmd *cmd, t_split *split, char *s)
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

t_cmd	*sh_split(char **s)
{
	t_cmd	*cmd;
	t_split	*split;
	char	*t;

	split = init_split();
	cmd = init_cmd();
	while (**s && (split->quote || split->par || !ft_strchr("&|", **s)))
	{
		t = handle_in_redirections(cmd, split, *s);
		t = handle_out_redirections(cmd, split, t);
		if (t == *s)
		{
			t = handle_quotes_and_parenthesis(cmd, split, *s);
			if (t == *s)
				cmd_list_add_char(cmd, split, *s);
			(*s)++;
		}
		else
			*s = t;
	}
	cmd->cmd = add_string(cmd->cmd, split->word);
	*s = handle_operator(cmd, *s);
	free(split);
	return (cmd);
}
