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

t_cmd	*sh_split(char *s)
{
	t_cmd	*cmd;
	char	*word;

	cmd = init_cmd();
	word = NULL;
	while (*s && !ft_strchr("()\"\'*<>|$=", *s))
	{
		if (*s != ' ')
			word = add_char(word, *s);
		else
		{
			cmd->cmd = add_string(cmd->cmd, word);
			word = NULL;
		}
		s++;
	}
	cmd->cmd = add_string(cmd->cmd, word);
	return (cmd);
}

/*t_cmd	*parse_cmd(char *str)
{
	t_cmd	*cmd;
	(void) str;
	cmd = init_cmd();

	return (cmd);
}
*/