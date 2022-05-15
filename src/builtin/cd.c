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
	}
	else
		chdir(cmd[1]);
}

static void	end_dir(char *start_dir, char **env)
{
	int		has_cd;
	char	*str;

	has_cd = (ft_strcmp(start_dir, getcwd(NULL, 0)) != 0);
	if (has_cd)
	{
		env_unset("OLDPWD", env);
		//str = ft_strjoin("OLDPWD=", getcwd(NULL, 0));
		//export(str, env);
		//free(str);
	}
	g_error = !has_cd;
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

void	change_directory(char **cmd, char **env)
{
	int		arg;
	char	*start_dir;

	start_dir = getcwd(NULL, 0);
	arg = 0;
	while (cmd[arg])
		arg++;
	if (arg > 2)
	{
		prompt_error("cd", "too many arguments\n");
		return ;
	}
	else if (arg == 1 || !ft_strcmp(cmd[1], "~"))
	{
		if (ft_getenv("HOME", env))
			chdir(ft_getenv("HOME", env));
		else
			prompt_error("cd", "HOME not set\n");
		return ;
	}
	if (wrong_dir(cmd) == -1)
		return ;
	one_arg(cmd, env);
	end_dir(start_dir, env);
}
