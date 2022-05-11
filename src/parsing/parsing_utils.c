/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 10:55:41 by jboumal           #+#    #+#             */
/*   Updated: 2022/05/11 10:55:43 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*file_error(void)
{
	perror("minishell");
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
