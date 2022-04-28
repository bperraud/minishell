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
		printf("               __\n              /o_)\n");
		printf("     _/\\/\\/\\_/ /\n   _|minishell/\n _|  (  | (  |\n");
		str = readline("/__.-'|_|--|_| ~ ");
		if (!str || !ft_strncmp(str, "exit", 5))
		{
			free(str);
			break ;
		}
		add_history(str);
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
