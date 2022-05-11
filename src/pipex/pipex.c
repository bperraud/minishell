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

int	pipex(char **cmd, char **envp)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		status;

	if (pipe(pipe_fd) < 0)
		exit(EXIT_FAILURE);
	pipe(pipe_fd);
	pid = fork();
	if (pid != 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		waitpid(-1, &status, 0);
	}
	else
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		exec_cmd(cmd, envp);
	}
	return (status);
}

int	multiple_cmd(t_list_cmd *list_cmd, char **envp)
{
	int	i;
	int	status;

	while (list_cmd)
	{
		printf("cmd : %s\n", list_cmd->command->cmd[0]);
		pipex(list_cmd->command->cmd, envp);
		if (!list_cmd->next)
		{
			list_cmd = list_cmd->next;
			break ;
		}
		list_cmd = list_cmd->next;
	}
	return (status);
}
