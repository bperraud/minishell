/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 12:19:04 by jboumal           #+#    #+#             */
/*   Updated: 2022/06/02 01:28:46 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_error = 0;

static int	inc_lvl(int lvl)
{
	if (lvl < 0)
		lvl = -1;
	else if (lvl > 999)
		lvl = 0;
	return (lvl + 1);
}

char	**increment_shlvl(char **env)
{
	char	*shlvl;
	char	*tmp;
	int		lvl;

	shlvl = ft_getenv("SHLVL", env);
	if (shlvl)
	{
		lvl = ft_atoi(shlvl);
		env = env_unset("SHLVL", env);
		free(shlvl);
	}
	else
		lvl = 0;
	lvl = inc_lvl(lvl);
	if (lvl != 1000)
		tmp = ft_itoa(lvl);
	else
		tmp = ft_sstrdup("");
	shlvl = ft_strjoin("SHLVL=", tmp);
	if (!shlvl)
		exit(ENOMEM);
	env = env_add(shlvl, env);
	free(tmp);
	free(shlvl);
	return (env);
}

int	main(int argc, char **argv, char **envp)
{
	char	**env;

	env = env_dup(envp);
	env = increment_shlvl(env);
	if (argc == 1)
	{
		start_shell(env, NULL);
	}
	if (argc == 3 && ft_strncmp(argv[1], "-c", 3) == 0)
	{
		start_shell(env, argv[2]);
	}
	return (g_error);
}
