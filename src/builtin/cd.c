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

void	change_directory(char **cmd, char **env)
{
	int		arg;
	char	*home_dir;
	char	*start_dir;

	start_dir = getcwd(NULL, 0);
	arg = 0;
	while (cmd[arg])
		arg++;
	if (arg > 3)
	{
		printf("minishell: cd: too many arguments\n");
		return ;
	}
	else if (arg == 1)
	{
		home_dir = ft_getenv("HOME", env);
		if (home_dir)
			chdir(ft_getenv("HOME", env));
		else
			printf("minishell: cd: HOME not set\n");
	}
	else
		chdir(cmd[1]);
}
