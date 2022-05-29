/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 00:59:45 by bperraud          #+#    #+#             */
/*   Updated: 2022/03/23 00:59:45 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*ft_strncpy(char *dest, const char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

void	free_all(char **cmd1, char **cmd2, char **path)
{
	free_tab(cmd1);
	free_tab(cmd2);
	free_tab(path);
}
