/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 00:32:20 by bperraud          #+#    #+#             */
/*   Updated: 2022/05/12 00:32:20 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd(t_list_cmd *list_cmd)
{
	if (!list_cmd)
	{
		printf("list is empty.\n");
		return ;
	}
	while (list_cmd)
	{
		printf("list command : %s\n", list_cmd->command->cmd[0]);
		list_cmd = list_cmd->next;
	}
}

t_list_cmd	*lst_last(t_list_cmd *list_cmd)
{
	if (!list_cmd)
		return (NULL);
	while (list_cmd->next)
		(list_cmd = list_cmd->next);
	return (list_cmd);
}

void	add_back(t_list_cmd **list_cmd, t_cmd *new)
{
	t_list_cmd	*t;
	t_list_cmd	*last;

	if (!(*list_cmd)->command)
	{
		(*list_cmd)->next = NULL;
		(*list_cmd)->command = new;
	}
	else
	{
		t = smalloc(sizeof(t_list_cmd));
		t->command = new;
		t->next = NULL;
		last = lst_last(*list_cmd);
		last->next = t;
	}
}

t_list_cmd	*init_list(void)
{
	t_list_cmd	*list_cmd;

	list_cmd = smalloc(sizeof(t_list_cmd));
	list_cmd->next = NULL;
	list_cmd->command = NULL;
	return (list_cmd);
}

void	free_list_cmd(t_list_cmd *list_cmd)
{
	t_list_cmd	*temp;

	if (list_cmd)
	{
		while (list_cmd)
		{
			temp = list_cmd->next;
			free_t_cmd(list_cmd->command);
			free(list_cmd);
			list_cmd = temp;
		}
	}
}
