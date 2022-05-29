/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:17:42 by bperraud          #+#    #+#             */
/*   Updated: 2022/05/29 16:17:42 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char	**pipe_subshell(t_cmd *command, char **envp)
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
	/*
	else if (!ft_strncmp(command->cmd[0], "./", 2)
		|| !ft_strncmp(command->cmd[0], "/", 1))
		ft_executable(command->cmd, envp);
	*/
	else
	{
		if (has_path(command->cmd[0], envp))
			extern_cmd(command, envp);
	}
	while (wait(NULL) > 0)
		;
	return (envp);
}

char	**launch_cmd_pipe(t_cmd *command, char **envp)
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
	else if (!ft_strncmp(command->cmd[0], "./", 2)
		|| !ft_strncmp(command->cmd[0], "/", 1))
		ft_executable(command->cmd, envp);
	else
	{
		if (has_path(command->cmd[0], envp))
			exec_cmd(command->cmd, envp);
	}
	return (envp);
}
