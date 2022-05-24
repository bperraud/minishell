/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:23:15 by jboumal           #+#    #+#             */
/*   Updated: 2022/05/24 16:13:41 by bperraud         ###   ########.fr       */
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
		printf("%s\n", env[i]);
		i++;
	}
}

void	ft_env_export(char **env)
{
	int	i;

	g_error = 0;
	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		printf("declare -x ");
		printf("%s\n", env[i]);
		i++;
	}
}
