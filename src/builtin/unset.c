/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:05:11 by jboumal           #+#    #+#             */
/*   Updated: 2022/05/26 14:08:24 by bperraud         ###   ########.fr       */
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
		if (correct_env_variable(cmd[i]))
		{
			str = ft_getenv(cmd[i], env);
			if (str)
			{
				env = env_unset(cmd[i], env);
				free(str);
			}
		}
	}
	return (env);
}
