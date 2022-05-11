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
	int	i;

	if (!list_cmd)
	{
		printf("list is empty.\n");
		return ;
	}
	i = 0;
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
		t = malloc(sizeof(t_list_cmd));
		t->command = new;
		t->next = NULL;
		last = lst_last(*list_cmd);
		last->next = t;
	}
}
