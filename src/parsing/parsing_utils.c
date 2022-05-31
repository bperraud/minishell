/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 10:55:41 by jboumal           #+#    #+#             */
/*   Updated: 2022/05/31 23:48:45 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	change_quote(char quote, char c)
{
	if (!quote)
		quote = c;
	else
		quote = '\0';
	return (quote);
}

char	*file_error(void)
{
	ft_putstr_fd("-minishell: file error\n", 2);
	g_error = FILE_ERROR;
	return (NULL);
}

void	cmd_list_add_char(t_cmd *cmd, t_split *split, char *s)
{
	if (ft_strchr("&|", *s) && split->par)
		split->word = add_char(split->word, *s);
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
