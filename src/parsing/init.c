/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 13:40:41 by jboumal           #+#    #+#             */
/*   Updated: 2022/04/13 13:40:42 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error	*init_error(void)
{
	t_error	*err;

	err = smalloc(sizeof(t_error));
	err->quote = '\0';
	err->par = 0;
	err->is_start_of_cmd = true;
	return (err);
}

t_split	*init_split(void)
{
	t_split	*split;

	split = smalloc(sizeof(t_split));
	split->par = 0;
	split->quote = '\0';
	split->word = NULL;
	return (split);
}

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = smalloc(sizeof(t_cmd));
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->here_doc = NULL;
	cmd->mode = NONE;
	cmd->cmd = NULL;
	return (cmd);
}
