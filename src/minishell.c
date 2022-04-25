/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 12:19:04 by jboumal           #+#    #+#             */
/*   Updated: 2022/04/26 00:43:12 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	command(t_cmd *cmd, char **envp)
{
	if (cmd->mode == PIPE)
		return (cmd_pipex(cmd, envp));
	else if (cmd->mode == AND)
		;
	else if (cmd->mode == OR)
		;
	else if (cmd->mode == NONE)
		;
}

void	sh(char *str, char **envp)
{
	t_cmd	*cmd;

	cmd = sh_split(&str);
	printf("cmd : %s\n", cmd->cmd[0]);
	command(cmd, envp);
	while (*str)
	{
		print_list(cmd->cmd);
		print_cmd_args(cmd);
		free_t_cmd(cmd);
		cmd = sh_split(&str);
	}
}

static void	start_shell(char **envp)
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
		sh(str, envp);
		free(str);
	}
}


int	main(int argc, char **argv, char **envp)
{
	if (argc == 1)
	{
		start_shell(envp);
	}
	(void) argv;
	system ("leaks minishell");
	return (0);
}


/*
int	main(int argc, char **argv, char **envp)
{
	start(argc, argv, envp);

	return (0);
}
*/
