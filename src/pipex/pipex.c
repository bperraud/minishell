/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 03:47:33 by bperraud          #+#    #+#             */
/*   Updated: 2022/03/30 03:47:33 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipex(t_cmd *command, char **envp)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		status;
	char	**cmd;

	cmd = command->cmd;
	if (pipe(pipe_fd) < 0)
		exit(EXIT_FAILURE);
	pipe(pipe_fd);
	pid = fork();
	if (pid != 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		command->fd_in = pipe_fd[0];
		waitpid(-1, &status, 0);
	}
	else
	{
		close(pipe_fd[0]);
		command->fd_out = pipe_fd[1];
		dup2(pipe_fd[1], 1);
		exec_cmd(cmd, envp);
	}
	g_error = status;
}

void	multiple_cmd(t_list_cmd *list_cmd, char **envp)
{
	while (list_cmd)
	{
		pipex(list_cmd->command, envp);
		if (!list_cmd->next)
			break;
		list_cmd = list_cmd->next;
	}
}
