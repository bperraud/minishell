/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 12:19:04 by jboumal           #+#    #+#             */
/*   Updated: 2022/04/08 12:19:06 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sh(char *str)
{
	t_cmd	*cmd;

	while (*str)
	{
		cmd = sh_split(&str);
		print_list(cmd->cmd);
		print_cmd_args(cmd);
		free_t_cmd(cmd);
	}
}

static void	start_shell(void)
{
	char	*str;

	while (1)
	{
		str = readline("\033[33m               __\n              /o_)\n     \
_/\\/\\/\\_/ /\n   _|minishell/\n _|  (  | (  |\n/__.-'|_|--|_| ~ \033[0m");

		if (!str || !ft_strncmp(str, "exit", 5))
		{
			free(str);
			break ;
		}
		sh(str);
		free(str);
	}
}

int	main(int argc, char **argv)
{
	if (argc == 1)
	{
		start_shell();
	}
	(void) argv;
	system ("leaks minishell");
	return (0);
}
