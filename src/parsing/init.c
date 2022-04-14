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

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
	{
		perror("error");
		exit(EXIT_FAILURE);
	}
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->here_doc = FALSE;
	cmd->append_out = FALSE;
	cmd->mode = NONE;
	cmd->cmd = NULL;
	cmd->next = NULL;
	return (cmd);
}
