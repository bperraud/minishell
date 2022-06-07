/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:23:15 by jboumal           #+#    #+#             */
/*   Updated: 2022/06/05 17:45:44 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char **env)
{
	int	i;

	g_error = 0;
	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		if (env[i][0] != '.') 
		{
			ft_putstr_fd(env[i], 1);
			ft_putstr_fd("\n", 1);
		}
		i++;
	}
}

void	ft_env_export(char **env)
{
	int	i;
	int	j;

	g_error = 0;
	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		j = 0;
		ft_putstr_fd("declare -x ", 1);
		while (env[i][j])
		{
			ft_putchar_fd(env[i][j], 1);
			if (env[i][j] == '=')
				ft_putstr_fd("\"", 1);
			if (!env[i][j + 1])
				ft_putstr_fd("\"\n", 1);
			j++;
		}
		i++;
	}
}
