/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:00:35 by bperraud          #+#    #+#             */
/*   Updated: 2022/06/01 17:00:35 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect(t_cmd *command, int fd_save[2])
{
	if (ft_strlen(command->here_doc))
		dup_close(here_doc(command->here_doc), 0);
	if (command->fd_in != 0)
		dup_close(command->fd_in, 0);
	if (command->fd_out != 1)
		dup_close(command->fd_out, 1);
}

void	restore_std(int fd_save[2])
{
	dup2(fd_save[0], STDIN);
	dup2(fd_save[1], STDOUT);
}
