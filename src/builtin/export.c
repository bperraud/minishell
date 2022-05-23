/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:05:06 by jboumal           #+#    #+#             */
/*   Updated: 2022/05/23 18:16:12 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**export(char *cmd, char **env)
{
	char	*var;
	char	*str;

	g_error = 0;
	if (!get_var_len(cmd))
		return (env);
	else
	{
		var = ft_strndup(cmd, get_var_len(cmd));
		str = ft_getenv(var, env);
		if (str)
			env = env_unset(var, env);
		free(var);
		free(str);
		return (env_add(cmd, env));
	}
}
