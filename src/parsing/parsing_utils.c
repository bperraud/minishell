/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 10:55:41 by jboumal           #+#    #+#             */
/*   Updated: 2022/05/15 00:29:55 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*file_error(void)
{
	perror("-minishell");
	g_error = FILE_ERROR;
	return (NULL);
}

void	cmd_list_add_char(t_cmd *cmd, t_split *split, char *s)
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
