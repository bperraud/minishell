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
		if (old_pwd)
			chdir(old_pwd);
		else
			prompt_error("cd", "OLDPWD not set\n");
		free(old_pwd);
		g_error = 1;
	}
	else
		chdir(cmd[1]);
}

static char	**end_dir(char **cmd, char *start_dir, int argc, char **env)
{
	int		has_cd;
	char	**str;
	char	*end_dir;

	end_dir = getcwd(NULL, 0);
	has_cd = (ft_strcmp(start_dir, end_dir) != 0);
	str = malloc(2 * sizeof(char));
	if (has_cd)
	{
		str[0] = NULL;
		str[1] = ft_strjoin("OLDPWD=", start_dir);
		str[2] = NULL;
		env = export(str, env);
		if (argc == 2 && !ft_strcmp(cmd[1], "-"))
			printf("%s\n", end_dir);
	}
	free(str[1]);
	free(str);
	free(end_dir);
	free(start_dir);
	return (env);
}

static int	wrong_dir(char **cmd)
{
	char	*str;

	if (!cmd[1] || !ft_strcmp(cmd[1], "-") || !ft_strcmp(cmd[1], "~"))
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

static char	**cd_home(char **cmd, char *start_dir, int argc, char **env)
{
	char	*home;

	home = ft_getenv("HOME", env);
	if (home)
		chdir(home);
	else
	{
		prompt_error("cd", "HOME not set\n");
		g_error = 1;
	}
	free(home);
	return (end_dir(cmd, start_dir, argc, env));
}

char	**change_directory(char **cmd, char **env)
{
	char	*start_dir;
	int		argc;

	argc = 0;
	while (cmd[argc])
		argc++;
	g_error = 0;
	if (argc > 2)
	{
		prompt_error("cd", "too many arguments\n");
		g_error = 1;
		return (env);
	}
	if (wrong_dir(cmd) == -1)
		return (env);
	start_dir = getcwd(NULL, 0);
	if (argc == 1 || !ft_strcmp(cmd[1], "~"))
		return (cd_home(cmd, start_dir, argc, env));
	one_arg(cmd, env);
	return (end_dir(cmd, start_dir, argc, env));
}
