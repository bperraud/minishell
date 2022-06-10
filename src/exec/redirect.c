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

void	error_file_exit(char *error)
{
	perror(error);
	g_error = FILE_ERROR;
	exit(FILE_ERROR);
}

void	dup_close(int fd, int std)
{
	if (dup2(fd, std) < 0)
	{
		error_file_exit("dup2");
	}
	close(fd);
}

void	redirect(t_cmd *command, int fd_save[2])
{
	pid_t	pid;

	if (ft_strlen(command->here_doc))
	{
		if (command->prev_cmd == PIPE)
		{
			pid = fork_protected();
			if (!pid)
			{
				if (fd_save)
					restore_std(fd_save);
				dup_close(here_doc(command->here_doc), STDIN);
				exit(0);
			}
			waitpid(pid, NULL, 0);
		}
		else
			dup_close(here_doc(command->here_doc), STDIN);
	}
	if (command->fd_in != STDIN && command->fd_in > 0)
		dup_close(command->fd_in, STDIN);
	if (command->fd_out != STDOUT && command->fd_out > 0)
		dup_close(command->fd_out, STDOUT);
}

void	restore_std(int fd_save[2])
{
	dup2(fd_save[0], STDIN);
	dup2(fd_save[1], STDOUT);
}
