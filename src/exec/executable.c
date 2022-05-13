/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 00:29:09 by bperraud          #+#    #+#             */
/*   Updated: 2022/05/13 00:29:09 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	ft_executable(char **cmd, char	**envp)
{
	int		status;

	if (test_access(cmd[0], READ) == FILE_ERROR)
		return ;
	if (!fork())
	{
		execve(cmd[0], cmd, envp);
		printf("-minishell: %s : command not found\n", cmd[0]);
		g_error = COMMAND_NOT_FOUND;
		exit(COMMAND_NOT_FOUND);
	}
	waitpid(-1, &status, 0);
}
