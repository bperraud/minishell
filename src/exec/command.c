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

char	**command(t_cmd *cmd, char **envp)
{
	if ((cmd->prev_cmd == AND && !g_error)
		|| (cmd->prev_cmd == OR && g_error))
		return (launch_cmd(cmd, envp));
	if (cmd->prev_cmd == OR && !g_error)
		g_error = OR_MODE_ERROR;
	return (envp);
}

void	exec_cmd(char **cmd_arg, char **envp)
{
	int		i;
	char	*cmd;
	char	**paths;

	i = -1;
	paths = parsing(envp);
	while (paths[++i])
	{
		cmd = create_path(paths[i], cmd_arg[0]);
		if (!cmd)
		{
			free_tab(paths);
			return ;
		}
		execve(cmd, cmd_arg, envp);
		free(cmd);
	}
	ft_putstr_fd(cmd_arg[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("command not found\n", 2);
	exit(COMMAND_NOT_FOUND);
}

/* redirect to appropriate function for a cmd */
char	**launch_cmd(t_cmd *command, char **envp)
{
	if (!ft_strcmp(command->cmd[0], "cd"))
		return (change_directory(command->cmd, envp));
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
	else
	{
		if (has_path(command->cmd[0], envp))
			extern_cmd(command, envp);
	}
	return (envp);
}

/* not build_in command */
void	extern_cmd(t_cmd *command, char **envp)
{
	int		status;

	status = 0;
	if (!fork_protected())
	{
		if (ft_strlen(command->here_doc))
			dup_close(here_doc(command->here_doc), 0);
		if (command->fd_in != 0)
			dup_close(command->fd_in, 0);
		if (command->fd_out != 1)
			dup_close(command->fd_out, 1);
		exec_cmd(command->cmd, envp);
	}
	waitpid(-1, &status, 0);
	if (ft_strlen(command->here_doc))
		unlink(HERE_DOC);
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
