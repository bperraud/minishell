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
	printf("minishell: %s : command not found\n", cmd_arg[0]);
	exit(FILE_ERROR);
}

/* redirect to appropriate function for a cmd */
int	launch_cmd(t_cmd *command, char **envp)
{
	if (!ft_strcmp(command->cmd[0], "cd"))
		return (change_directory(command->cmd));
	else if (!ft_strcmp(command->cmd[0], "echo"))
		return (echo(command->cmd));
	else if (!ft_strcmp(command->cmd[0], "export"))
	{
		export(command->cmd[1], envp);
		return 0;
	}
	else
		return (extern_cmd(command, envp));
	return (-1);
}

/* not build_in command */
int	extern_cmd(t_cmd *command, char **envp)
{
	int	status;

	if (command->mode == PIPE)
		redirect_pipe(command, envp);
	if (!fork())
	{
		if (command->fd_in != 0)	// lire l'entrée dans fd_in
			dup_close(command->fd_in, 0);
		if (command->fd_out != 1)	// rediriger la sortie vers fd_out
			dup_close(command->fd_out, 1);
		exec_cmd(command->cmd, envp);
	}
	waitpid(-1, &status, 0);
	return (status);
}
