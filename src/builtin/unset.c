/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:05:11 by jboumal           #+#    #+#             */
/*   Updated: 2022/06/10 18:11:49 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**unset(char **cmd, char **env)
{
	char	*str;
	int		i;

	i = 0;
	g_error = 0;
	while (cmd[++i])
	{
		str = ft_getenv(cmd[i], env);
		if (cmd[i][0] != '.' && str)
		{
			env = env_unset(cmd[i], env);
			free(str);
		}
	}
	return (env);
}
