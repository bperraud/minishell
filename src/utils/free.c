/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <jboumal@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 10:04:18 by jboumal           #+#    #+#             */
/*   Updated: 2022/04/17 10:04:21 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_t_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->cmd)
		free_str_list(cmd->cmd);
	if (cmd->next)
		free_t_cmd(cmd->next);
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
