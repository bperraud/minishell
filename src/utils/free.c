/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 10:04:18 by jboumal           #+#    #+#             */
/*   Updated: 2022/05/23 18:06:04 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_and_return(char *str, void *ptr, int r_value)
{
	if (str)
		free(str);
	free(ptr);
	return (r_value);
}

void	free_t_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->cmd)
		free_str_list(cmd->cmd);
	if (cmd->here_doc)
		free(cmd->here_doc);
	free(cmd);
}

void	free_str_list(char **list)
{
	char	**t;

	if (!list)
		return ;
	t = list;
	while (*t)
	{
		free(*t);
		t++;
	}
	free(list);
}
