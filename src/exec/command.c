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

int	exec_cmd(char **cmd_arg, char **envp)
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
			return (-1);
		}
		execve(cmd, cmd_arg, envp);
		free(cmd);
	}
	printf("-minishell: %s : command not found\n", cmd_arg[0]);
	return (COMMAND_NOT_FOUND);
}

/* redirect to appropriate function for a cmd */
char	**launch_cmd(t_cmd *command, char **envp)
{
	if (!ft_strcmp(command->cmd[0], "cd"))
		change_directory(command->cmd, envp);
	else if (!ft_strcmp(command->cmd[0], "echo"))
		echo(command->cmd);
	else if (!ft_strcmp(command->cmd[0], "export"))
		return (export(command->cmd[1], envp));
	else if (!ft_strcmp(command->cmd[0], "unset"))
		return (unset(command->cmd[1], envp));
	else if (!ft_strcmp(command->cmd[0], "env"))
		ft_env(envp);
	else if (!ft_strcmp(command->cmd[0], "pwd"))
		pwd();
	else if (!ft_strcmp(command->cmd[0], "exit"))
		ft_exit(command);
	else if (!ft_strncmp(command->cmd[0], "./", 2))
		ft_executable(command->cmd, envp);
	else
		extern_cmd(command, envp);
	return (envp);
}

/* not build_in command */
void	extern_cmd(t_cmd *command, char **envp)
{
	int	status;
	int	exit_value;

	exit_value = 0;
	if (!fork())
	{
		if (ft_strlen(command->here_doc))
			dup_close(here_doc(command->here_doc), 0);
		if (command->fd_in != 0)
			dup_close(command->fd_in, 0);
		if (command->fd_out != 1)
			dup_close(command->fd_out, 1);
		exit_value = exec_cmd(command->cmd, envp);
	}
	waitpid(-1, &status, 0);
	if (ft_strlen(command->here_doc))
		unlink(HERE_DOC);
	g_error = exit_value;
}
