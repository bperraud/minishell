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
	if (pid < 0)
	{
		error_file_exit("fork");
	}
	return (pid);
}

static void	pipex(t_cmd *command, char **envp)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		error_file_exit("pipe");
	pid = fork_protected();
	if (pid != 0)
	{
		close(pipe_fd[1]);
		if (command->fd_in == STDIN)
			dup2(pipe_fd[0], STDIN);
		close(pipe_fd[0]);
		if (!has_path(envp) || !is_cmd_in_path(command->cmd[0], envp))
		{
			waitpid(pid, NULL, 0);
			close(0);
		}
	}
	else
	{
		close(pipe_fd[0]);
		if (command->fd_out == STDOUT)
			dup2(pipe_fd[1], STDOUT);
		close(pipe_fd[1]);
		subshell(command, envp);
		close(1);
		exit(0);
	}
}

static void	multiple_cmd(t_list_cmd *list_cmd, char **envp)
{
	while (list_cmd)
	{
		pipex(list_cmd->command, envp);
		if (!list_cmd->next)
			break ;
		list_cmd = list_cmd->next;
	}
}

void	pipe_cmd(char **str, char **envp, t_cmd **cmd)
{
	t_list_cmd	*list_cmd;
	t_cmd		*f_cmd;

	if ((*cmd)->mode != PIPE || *skip_spaces(*str) == '\0')
		return ;
	list_cmd = init_list();
	while ((*cmd)->mode == PIPE)
	{
		add_back(&list_cmd, *cmd);
		*cmd = init_cmd(0);
		*str = get_next_cmd(*str, envp, *cmd);
	}
	f_cmd = list_cmd->command;
	if ((f_cmd->prev_cmd == AND && g_error)
		|| (f_cmd->prev_cmd == OR && !g_error))
	{
		free_list_cmd(list_cmd);
		return ;
	}
	multiple_cmd(list_cmd, envp);
	(*cmd)->prev_cmd = PIPE;
	free_list_cmd(list_cmd);
}
