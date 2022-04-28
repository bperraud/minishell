/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 15:05:48 by jboumal           #+#    #+#             */
/*   Updated: 2022/04/14 15:05:49 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd_args(t_cmd *cmd)
{
	if (!cmd)
		return ;
	printf("~ infile is \033[32m%d.\n\033[0m", cmd->fd_in);
	printf("~ outfile is \033[32m%d.\n\033[0m", cmd->fd_out);
	if (cmd->here_doc)
		printf("~ here_doc is \033[32m%s.\n\033[0m", cmd->here_doc);
	printf("~ mode is \033[32m%d.\n\033[0m", cmd->mode);
}

void	print_list(char **lst)
{
	int	i;

	if (!lst)
	{
		printf("cmd is empty.\n");
		return ;
	}
	i = 0;
	while (*lst)
	{
		printf("%s\n", *lst);
		lst ++;
		i++;
	}
	printf("~ printed \033[31m%d\033[0m elements.\n", i);
}
