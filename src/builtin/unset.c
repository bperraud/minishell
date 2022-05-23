/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:05:11 by jboumal           #+#    #+#             */
/*   Updated: 2022/05/23 18:16:18 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**unset(char *var, char **env)
{
	char	*str;

	g_error = 0;
	str = ft_getenv(var, env);
	if (!str)
	{
		free(str);
		return (env);
	}
	free(str);
	return (env_unset(var, env));
}
