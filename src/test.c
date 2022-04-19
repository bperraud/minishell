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
	if (cmd->fd_in)
		printf("infile is \033[32m%d\n\033[0m", cmd->fd_in);
	if (cmd->fd_out)
		printf("outfile is \033[32m%d\n\033[0m", cmd->fd_out);
	if (cmd->here_doc)
		printf("here_doc is \033[32m%s\n\033[0m", cmd->here_doc);
}

void	print_list(char **lst)
{
	int	i;

	if (!lst)
	{
		perror("error");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (*lst)
	{
		printf("%s\n", *lst);
		lst ++;
		i++;
	}
	printf("\033[31mprinted %d elements\033[0m\n", i);
}
