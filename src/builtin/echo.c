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
	ssize_t	len;

	option = false;
	i = 0;
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
		len = ft_strlen(cmd[i]);
		if (write(1, cmd[i], len) != len || (write(1, " ", 1) != 1))
			return ;
	}
	if (!option)
		ft_putstr_fd("\n", 1);
}
