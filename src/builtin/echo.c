/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 03:46:44 by bperraud          #+#    #+#             */
/*   Updated: 2022/05/01 03:46:44 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_empty_no_flag(char **cmd)
{
	if (!cmd[1])
	{
		ft_putstr_fd("\n", 1);
		return (true);
	}
	return (false);
}

void	echo(char **cmd)
{
	int		i;
	bool	option;

	option = false;
	i = 0;
	g_error = 0;
	if (is_empty_no_flag(cmd))
		return ;
	if (!ft_strcmp(cmd[1], "-n"))
	{
		if (!cmd[2])
			return ;
		option = true;
		i++;
	}
	while (cmd[++i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1])
			ft_putstr_fd(" ", 1);
	}
	if (!option)
		ft_putstr_fd("\n", 1);
}
