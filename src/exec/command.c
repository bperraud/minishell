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
	printf("-minishell: %s : command not found\n", cmd_arg[0]);
	exit(FILE_ERROR);
}

/* redirect to appropriate function for a cmd */
char **launch_cmd(t_cmd *command, char **envp)
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
	else
		extern_cmd(command, envp);
	return (envp);
}

/* not build_in command */
void	extern_cmd(t_cmd *command, char **envp)
{
	int	status;

	if (!fork())
	{
		if (command->fd_in != 0)	// lire l'entrée dans fd_in
			dup_close(command->fd_in, 0);
		if (command->fd_out != 1)	// rediriger la sortie vers fd_out
			dup_close(command->fd_out, 1);
		exec_cmd(command->cmd, envp);
	}
	waitpid(-1, &status, 0);
}
