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

static void	child_process(int pipe_fd[2], int fd[2], t_cmd *cmd, char **envp)
{
	close(pipe_fd[0]);
	if (cmd->fd_out == STDOUT)
		dup_close(pipe_fd[1], STDOUT);
	subshell(cmd, fd, envp);
	close(1);
	exit(0);
}

static void	pipex(t_cmd *command, int fd_save[2], char **envp)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		error_file_exit("pipe");
	pid = fork_protected();
	if (pid != 0)
	{
		close(pipe_fd[1]);
		dup_close(pipe_fd[0], STDIN);
		if (!has_path(envp) || !is_cmd_in_path(command->cmd[0], envp)
			|| ft_strlen(command->here_doc))
			waitpid(pid, NULL, 0);
	}
	else
		child_process(pipe_fd, fd_save, command, envp);
}

static void	multiple_cmd(t_list_cmd *list_cmd, int fd_save[2], char **envp)
{
	while (list_cmd)
	{
		pipex(list_cmd->command, fd_save, envp);
		if (!list_cmd->next)
			break ;
		list_cmd = list_cmd->next;
	}
}

void	pipe_cmd(char **str, char **envp, int fd_save[2], t_cmd **cmd)
{
	t_list_cmd	*list_cmd;
	t_cmd		*f_cmd;

	if ((*cmd)->mode != PIPE || *skip_spaces(*str) == '\0')
		return ;
	list_cmd = init_list();
	while ((*cmd)->mode == PIPE)
	{
		if ((*cmd)->cmd)
			add_back(&list_cmd, *cmd);
		*cmd = init_cmd(0);
		*str = get_next_cmd(*str, envp, *cmd);
		(*cmd)->prev_cmd = PIPE;
	}
	f_cmd = list_cmd->command;
	if ((f_cmd->prev_cmd == AND && g_error)
		|| (f_cmd->prev_cmd == OR && !g_error))
	{
		free_list_cmd(list_cmd);
		return ;
	}
	multiple_cmd(list_cmd, fd_save, envp);
	(*cmd)->prev_cmd = PIPE;
	free_list_cmd(list_cmd);
}
