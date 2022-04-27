/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
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

	paths = parsing(envp);
	i = -1;
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
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_arg[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(128);
}

int	single_cmd(t_cmd *command, char**envp)
{
	int	status;

	if (!fork())
		exec_cmd(command->cmd, envp);
	waitpid(-1, &status, 0);
	return (status);
}


int		cmd_and(t_cmd *command, char **envp)
{
	;
}


int	change_directory()
{
	return (0);
}
