/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:05:06 by jboumal           #+#    #+#             */
/*   Updated: 2022/05/03 19:05:24 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**export(char *cmd, char **env)
{
	char	*var;

	if (!get_var_len(cmd))
		return (env);
	else
	{
		var = ft_strndup(cmd, get_var_len(cmd));
		if (ft_getenv(var, env))
			env = env_unset(var, env);
		free(var);
		return (env_add(env, cmd));
	}
}
