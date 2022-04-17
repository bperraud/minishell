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

static void	change_quote(t_split *split, char c)
{
	if (!split->quote)
		split->quote = c;
	else
		split->quote = '\0';
}

static void	handle_quotes_and_parenthesis(t_cmd *cmd, t_split *split, char *s)
{
	if ((*s == '\'' || *s == '\"')
		&& (split->quote == *s || !split->quote) && !split->par)
		change_quote(split, *s);
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

/* split string s in list of substrings ;
	split will ignore spaces if quotes or parenthesis are opened
*/
t_cmd	*sh_split(char *s)
{
	t_cmd	*cmd;
	t_split	*split;

	split = init_split();
	cmd = init_cmd();
	while (*s)
	{
		handle_quotes_and_parenthesis(cmd, split, s);
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
		s++;
	}
	cmd->cmd = add_string(cmd->cmd, split->word);
	free(split);
	return (cmd);
}
