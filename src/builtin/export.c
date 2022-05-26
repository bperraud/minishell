/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:05:06 by jboumal           #+#    #+#             */
/*   Updated: 2022/05/26 13:53:27 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**export(char **cmd, char **env)
{
	char	*var;
	char	*str;
	int		i;

	g_error = 0;
	i = 0;
	if (!cmd[1])
	{
		ft_env_export(env);
		return (env);
	}
	while (cmd[++i])
	{
		if (correct_env_variable(cmd[i]))
		{
			var = ft_strndup(cmd[i], get_var_len(cmd[i]));
			str = ft_getenv(var, env);
			if (str)
				env = env_unset(var, env);
			free(var);
			free(str);
			env = env_add(cmd[i], env);
		}
	}
	return (env);
}
