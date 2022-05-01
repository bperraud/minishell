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

# include "minishell.h"

static void	e_option(char **cmd)
{
	;

}

static void	P_option(char **cmd)
{
	;
}

static void	L_option(char **cmd)
{
	;
}

static void	at_option(char **cmd)
{
	;
}


int	change_directory(char **cmd)
{
	int	arg;

	arg = 0;
	while (cmd[arg])
		arg++;

	if (arg > 3 || (arg == 3 && cmd[1][0] != '-'))
	{
		ft_printf("minishell: cd: too many arguments\n");
		return (1);
	}
	else if (arg == 3 && cmd[1][0] != '-' && (cmd[1][0] != 'P' || cmd[1][0] != 'L'
	 || cmd[1][0] != 'e' || cmd[1][0] != '@'))
	{
		ft_printf("minishell: cd: invalid option\n");
		return (1);
	}

	if (ft_strcmp(cmd[1], "-e"))
		e_option(cmd);
	else if (ft_strcmp(cmd[1], "-P"))
		P_option(cmd);
	else if (ft_strcmp(cmd[1], "-L"))
		L_option(cmd);
	else if (ft_strcmp(cmd[1], "-@"))
		at_option(cmd);


	else if (arg == 1)
		chdir(getenv("HOME"));



	// The return status is zero if the directory is successfully changed, non-zero otherwise.
	return (0);
}
