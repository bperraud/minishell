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

#include "minishell.h"

void	launch_cmd_pipe(t_cmd *command, char **envp)
{
	g_error = 0;
	if (!ft_strcmp(command->cmd[0], "cd"))
		change_directory(command, envp);
	else if (!ft_strcmp(command->cmd[0], "echo"))
		echo(command->cmd);
	else if (!ft_strcmp(command->cmd[0], "env"))
		ft_env(envp);
	else if (!ft_strcmp(command->cmd[0], "pwd"))
		pwd();
	else if (!ft_strncmp(command->cmd[0], "./", 2)
		|| !ft_strncmp(command->cmd[0], "/", 1))
		ft_executable(command->cmd, envp);
	else if (!ft_strcmp(command->cmd[0], "exit"))
		;
	else
	{
		if (has_path(command->cmd[0], envp))
			exec_cmd(command->cmd, envp);
	}
}
