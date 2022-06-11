/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 02:07:35 by bperraud          #+#    #+#             */
/*   Updated: 2022/05/12 02:07:35 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_cmd *cmd)
{
	cmd->fd_in = EXIT_CODE;
}

static bool	has_no_digit(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

static void	print_exit(char *str)
{
	ft_putstr_fd("-minishell: exit: ", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd(": numeric argument required\n", 1);
	g_error = 255;
}

void	try_exit(t_cmd *command, char *str, char **envp)
{
	int	arg;

	if (command->fd_in != EXIT_CODE)
		return ;
	arg = 0;
	while (command->cmd[arg])
		arg++;
	if (arg > 2)
	{
		prompt_error("exit", "too many arguments\n");
		return ;
	}
	ft_putstr_fd("exit\n", 1);
	if (arg == 2)
	{
		if (!has_no_digit(command->cmd[1]))
			print_exit(command->cmd[1]);
		else
			g_error = ft_atoi(command->cmd[1]);
	}
	free_t_cmd(command);
	free(str);
	free_str_list(envp);
	exit(g_error);
}
