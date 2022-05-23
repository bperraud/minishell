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

pid_t	fork_protected(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < -1)
	{
		perror("-minishell");
		exit(-1);
	}
	return (pid);
}

void	pipex(t_cmd *command, char **envp)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		status;

	status = 0;
	if (pipe(pipe_fd) < 0)
	{
		perror("-minishell");
		exit(-1);
	}
	pid = fork_protected();
	if (pid != 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		command->fd_in = pipe_fd[0];
	}
	else
	{
		close(pipe_fd[0]);
		command->fd_out = pipe_fd[1];
		dup2(pipe_fd[1], 1);
		exec_cmd(command->cmd, envp);
	}
	g_error = WEXITSTATUS(status);
}

void	multiple_cmd(t_list_cmd *list_cmd, char **envp)
{
	while (list_cmd)
	{
		pipex(list_cmd->command, envp);
		if (!list_cmd->next)
			break ;
		list_cmd = list_cmd->next;
	}
	while (wait(NULL) > 0)
		;
}

void	pipe_cmd(char **str, char **envp, t_cmd **cmd)
{
	t_list_cmd	*list_cmd;

	if ((*cmd)->mode != PIPE)
		return ;
	list_cmd = init_list();
	while ((*cmd)->mode == PIPE)
	{
		add_back(&list_cmd, *cmd);
		*cmd = init_cmd(AND);
		*str = get_next_cmd(*str, envp, *cmd);
	}
	multiple_cmd(list_cmd, envp);
	free_list_cmd(list_cmd);
}
