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

void	try_exit(t_cmd *cmd, t_cmd *prev_cmd, char *str)
{
	if (cmd->fd_in == EXIT_CODE)
	{
		free_t_cmd(prev_cmd);
		free(str);
		exit (g_error);
	}
}
