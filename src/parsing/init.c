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

t_split	*init_split(void)
{
	t_split	*split;

	split = malloc(sizeof(t_split));
	if (!split)
	{
		perror("error");
		exit(EXIT_FAILURE);
	}
	split->par = 0;
	split->quote = '\0';
	split->word = NULL;
	return (split);
}

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
	cmd->here_doc = false;
	cmd->append_out = false;
	cmd->mode = NONE;
	cmd->cmd = NULL;
	cmd->next = NULL;
	return (cmd);
}
