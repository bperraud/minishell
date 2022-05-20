/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 22:56:25 by bperraud          #+#    #+#             */
/*   Updated: 2022/04/30 22:56:25 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	one_arg(char **cmd, char **env)
{
	char	*old_pwd;

	if (!ft_strcmp(cmd[1], "-"))
	{
		old_pwd = ft_getenv("OLDPWD", env);
		//free(old_pwd);
		if (old_pwd)
			chdir(old_pwd);
		else
			prompt_error("cd", "OLDPWD not set\n");
		free(old_pwd);
	}
	else
		chdir(cmd[1]);
}

static char	**end_dir(char *start_dir, char **env)
{
	int		has_cd;
	char	*str;
	char	*end_dir;

	end_dir = getcwd(NULL, 0);
	has_cd = (ft_strcmp(start_dir, end_dir) != 0);
	if (has_cd)
	{
		//env = env_unset("OLDPWD", env);
		str = ft_strjoin("OLDPWD=", start_dir);
		env = env_add(str, env);
		free(str);
	}
	free(end_dir);
	free(start_dir);
	g_error = !has_cd;
	return (env);
}

static int	wrong_dir(char **cmd)
{
	char	*str;

	if (!ft_strcmp(cmd[1], "-"))
		return (0);
	if (test_access(cmd[1], READ) == 1)
		return (-1);
	if (!is_directory(cmd[1]))
	{
		str = ft_strjoin("cd: ", cmd[1]);
		prompt_error(str, "Not a directory\n");
		free(str);
		g_error = FILE_ERROR;
		return (-1);
	}
	return (0);
}

char	**change_directory(char **cmd, char **env)
{
	int		arg;
	char	*start_dir;
	char	*home;

	start_dir = getcwd(NULL, 0);
	arg = 0;
	while (cmd[arg])
		arg++;
	if (arg > 2)
	{
		prompt_error("cd", "too many arguments\n");
		return (env);
	}
	else if (arg == 1 || !ft_strcmp(cmd[1], "~"))
	{
		home = ft_getenv("HOME", env);
		if (home)
			chdir(home);
		else
			prompt_error("cd", "HOME not set\n");
		free(home);
		return (env);
	}
	if (wrong_dir(cmd) == -1)
		return (env);
	one_arg(cmd, env);
	return (end_dir(start_dir, env));
}
