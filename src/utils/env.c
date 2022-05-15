/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 20:20:04 by jboumal           #+#    #+#             */
/*   Updated: 2022/05/15 22:34:12 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	env_var_name_cmp(char *str, char *var_name)
{
	int	i;

	i = 0;
	while (var_name[i])
	{
		if (str[i] != var_name[i])
			return (false);
		i++;
	}
	if (str[i] == '=')
		return (true);
	else
		return (false);
}

char	*ft_getenv(char *str, char **env)
{
	int	i;
	int	j;

	i = 0;
	if (ft_strcmp(str, "?") == 0)
		return (ft_itoa(g_error));
	while (env[i])
	{
		if (env_var_name_cmp(env[i], str))
		{
			j = 0;
			while (env[i][j] != '=')
			{
				j++;
			}
			return (env[i] + j + 1);
		}
		i++;
	}
	return (NULL);
}

char	**env_unset(char *var, char **env)
{
	char	**new_env;
	int		i;
	int		j;

	new_env = smalloc(lst_len(env) * sizeof (char *));
	i = 0;
	j = 0;
	while (i < lst_len(env))
	{
		if (env_var_name_cmp(env[i], var))
		{
			free(env[i]);
		}
		else
		{
			new_env[j] = ft_strndup(env[i], ft_strlen(env[i]));
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}

char	**env_add(char *str, char **env)
{
	char	**new_env;
	int		i;

	new_env = smalloc((lst_len(env) + 2) * sizeof (char *));
	i = 0;
	while (i < lst_len(env))
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			perror("-minishell");
			exit(ENOMEM);
		}
		i++;
	}
	new_env[i] = ft_strndup(str, ft_strlen(str));
	new_env[i + 1] = NULL;
	return (new_env);
}

char	**env_dup(char **envp)
{
	char	**new_env;
	int		i;

	new_env = smalloc((lst_len(envp) + 1) * sizeof (char *));
	i = 0;
	while (i < lst_len(envp))
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
		{
			perror("-minishell");
			exit(ENOMEM);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}
