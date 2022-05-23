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
		printf("\n");
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
		printf("%s", cmd[i]);
		if (cmd[i + 1])
			printf(" ");
	}
	if (!option)
		printf("\n");
	g_error = 0;
}
