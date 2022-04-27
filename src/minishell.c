/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 12:19:04 by jboumal           #+#    #+#             */
/*   Updated: 2022/04/28 01:42:26 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	command(t_cmd *cmd, t_cmd *last_cmd, char **envp)
{
	if (last_cmd->exit_value == -1 && cmd->mode == OR)
		last_cmd->exit_value = 1;
	else if (last_cmd->exit_value == -1)
		last_cmd->exit_value = 0;
	if (cmd->mode == PIPE)
		return (cmd_pipe(cmd, envp));
	else if (last_cmd->mode == AND && !last_cmd->exit_value)
		return (single_cmd(cmd, envp));
	else if (last_cmd->mode == OR && last_cmd->exit_value)
		return (single_cmd(cmd, envp));
	else if (cmd->mode == NONE)
		return 0;
}

void	sh(char *str, char **envp)
{
	t_cmd	*cmd;
	t_cmd	*last_cmd;
	int		first;

	first = 1;
	int i = 2;
	last_cmd = malloc(sizeof(t_cmd));
	last_cmd->exit_value = -1;
	last_cmd->mode = AND;
	//while (*str)
	while (i--)
	{
		cmd = sh_split(&str);
		cmd->exit_value = command(cmd, last_cmd, envp);
		printf("exit status = %i\n", cmd->exit_value);
		print_list(cmd->cmd);
		print_cmd_args(cmd);
		last_cmd = cmd;

		//free_t_cmd(last_cmd);
	}
}

static void	start_shell(char **envp)
{
	char	*str;
	t_cmd	*cmd;

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
