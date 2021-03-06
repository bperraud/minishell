/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 18:15:37 by bperraud          #+#    #+#             */
/*   Updated: 2022/04/25 18:15:37 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* redirect to appropriate function for a cmd */
static char	**launch_cmd(t_cmd *command, char **envp, int fd_save[2])
{
	if (!ft_strcmp(command->cmd[0], "cd"))
		return (change_directory(command, envp));
	else if (!ft_strcmp(command->cmd[0], "echo"))
		echo(command->cmd);
	else if (!ft_strcmp(command->cmd[0], "export"))
		return (export(command->cmd, envp));
	else if (!ft_strcmp(command->cmd[0], "unset"))
		return (unset(command->cmd, envp));
	else if (!ft_strcmp(command->cmd[0], "env"))
		ft_env(envp);
	else if (!ft_strcmp(command->cmd[0], "pwd"))
		pwd();
	else if (!ft_strcmp(command->cmd[0], "exit"))
		ft_exit(command);
	else if (!ft_strncmp(command->cmd[0], "./", 2)
		|| !ft_strncmp(command->cmd[0], "/", 1))
		ft_executable(command->cmd, envp);
	else if (command->cmd[0][0] == '(')
		subshell(command, fd_save, envp);
	else
		extern_cmd(command, envp);
	while (wait(NULL) > 0)
		;
	return (envp);
}

char	**command(t_cmd *cmd, int fd_save[2], char **envp)
{
	if (!cmd->cmd)
		return (envp);
	if (cmd->prev_cmd == PIPE)
	{
		subshell(cmd, fd_save, envp);
		while (wait(NULL) > 0)
			;
	}
	else if ((cmd->prev_cmd == AND && !g_error)
		|| (cmd->prev_cmd == OR && g_error))
	{
		if (cmd->cmd[0][0] != '(')
			redirect(cmd, NULL);
		return (launch_cmd(cmd, envp, fd_save));
	}
	return (envp);
}

static void	exec_cmd(char **cmd_arg, char **envp)
{
	int		i;
	char	*cmd;
	char	**paths;

	i = -1;
	paths = parsing_path(envp);
	while (paths[++i])
	{
		cmd = create_path(paths[i], cmd_arg[0]);
		execve(cmd, cmd_arg, envp);
		free(cmd);
	}
	ft_putstr_fd(cmd_arg[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("command not found\n", 2);
	exit(COMMAND_NOT_FOUND);
}

/* not build_in command */
void	extern_cmd(t_cmd *command, char **envp)
{
	int		status;
	pid_t	pid;

	status = 0;
	g_error = 0;
	pid = fork_protected();
	if (!pid)
	{
		if (has_path(envp))
			exec_cmd(command->cmd, envp);
		else
			prompt_error(command->cmd[0], "No such file or directory\n");
		exit(COMMAND_NOT_FOUND);
	}
	waitpid(pid, &status, 0);
	if (g_error == 0)
		g_error = WEXITSTATUS(status);
}

void	ft_executable(char **cmd, char	**envp)
{
	int	status;
	int	access;

	status = 0;
	access = test_access(cmd[0], READ);
	if (access == NOT_EXECUTABLE || access == FILE_ERROR)
		return ;
	if (is_directory(cmd[0]))
	{
		prompt_error(cmd[0], "Is a directory\n");
		g_error = FILE_ERROR;
		return ;
	}
	if (!fork_protected())
	{
		execve(cmd[0], cmd, envp);
		prompt_error(cmd[0], "command not found\n");
		exit(COMMAND_NOT_FOUND);
	}
	waitpid(-1, &status, 0);
	g_error = WEXITSTATUS(status);
}
