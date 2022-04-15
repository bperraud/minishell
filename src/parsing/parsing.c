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

static char	change_quote(char quote, char c)
{
	if (!quote)
		return (c);
	else
		return ('\0');
}

/* split string s in list of substrings ;
	split will ignore spaces if quotes or parenthesis are opened
*/
t_cmd	*sh_split(char *s)
{
	t_cmd	*cmd;
	char	*word;
	char	quote;
	int		parenthesis;

	parenthesis = 0;
	quote = '\0';
	cmd = init_cmd();
	word = NULL;
	while (*s)
	{
		if ((*s == '\'' || *s == '\"') && (quote == *s || !quote) && !parenthesis)
			quote = change_quote(quote, *s);
		else if (!quote && *s == '(')
			parenthesis ++;
		else if (!quote && *s == ')')
			parenthesis --;
		if (!ft_strchr("*<>&|$", *s))
		{
			if (parenthesis || quote || *s != ' ')
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
