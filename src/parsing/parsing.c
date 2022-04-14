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

static char	change_quote(quote, c)
{
	if (!quote)
		return (c);
	else if (quote == c)
		return ('\0');
	else
		return (quote);
}

t_cmd	*sh_split(char *s)
{
	t_cmd	*cmd;
	char	*word;
	char	quote;

	quote = '\0';
	cmd = init_cmd();
	word = NULL;
	while (*s)
	{
		if (*s == '\'' || *s == '\"')
			quote = change_quote(quote, *s);
		if (!ft_strchr("()\"\'*<>|$=", *s))
		{
			if (quote || *s != ' ')
				word = add_char(word, *s);
			else
			{
				cmd->cmd = add_string(cmd->cmd, word);
				word = NULL;
			}
		}
		s++;
	}
	cmd->cmd = add_string(cmd->cmd, word);
	return (cmd);
}
