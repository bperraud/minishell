/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 02:07:35 by bperraud          #+#    #+#             */
/*   Updated: 2022/05/12 02:07:35 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_cmd *cmd)
{
	cmd->fd_in = EXIT_CODE;
}

void	try_exit(t_cmd *command, char *str, char **envp)
{
	int	arg;

	if (command->fd_in != EXIT_CODE)
		return ;
	arg = 0;
	while (command->cmd[arg])
		arg++;
	if (arg > 2)
	{
		prompt_error("exit", "too many arguments\n");
		return ;
	}
	if (arg == 2)
		g_error = ft_atoi(command->cmd[1]);
	free_t_cmd(command);
	free(str);
	free_str_list(envp);
	ft_putstr_fd("exit\n", 1);
	exit(g_error);
}
