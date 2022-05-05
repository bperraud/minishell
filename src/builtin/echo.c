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

int	echo(char **cmd)
{
	int		i;
	int		option;
	ssize_t	len;

	option = 0;
	i = 0;
	if (!ft_strcmp(cmd[1], "-n"))
	{
		option = 1;
		i++;
	}
	while (cmd[++i])
	{
		len = ft_strlen(cmd[i]);
		if (write(1, cmd[i], len) != len || (write(1, " ", 1) != 1))
			return (-1);
	}
	if (!option)
	{
		if (write(1, "\n", 2) != 2)
			return (-1);
	}
	return (0);
}
