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

void	exec_cmd_minishell(char **cmd_arg, char **envp)
{
	int		i;
	char	*cmd;
	char	**paths;

	paths = parsing(envp);
	//cmd_arg = split_arg(arg, ' ');
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

void	exec_cmd(char *arg, char **envp)
{
	int		i;
	char	*cmd;
	char	**paths;
	char	**cmd_arg;

	paths = parsing(envp);
	cmd_arg = split_arg(arg, ' ');
	i = -1;
	while (paths[++i])
	{
		cmd = create_path(paths[i], cmd_arg[0]);
		if (!cmd)
		{
			free_tab(cmd_arg);
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

int	change_directory()
{
	return (0);
}
