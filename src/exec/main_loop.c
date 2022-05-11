/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 01:27:04 by bperraud          #+#    #+#             */
/*   Updated: 2022/05/12 01:29:48 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**command(t_cmd *cmd, t_cmd *prev_cmd, char **envp)
{
	if ((prev_cmd->mode == AND && !prev_cmd->exit_value)
		|| (prev_cmd->mode == OR && prev_cmd->exit_value))
		return (launch_cmd(cmd, envp));
	return (NULL);
}

char	**sh(char *str, char **envp)
{
	t_cmd		*cmd;
	t_cmd		*prev_cmd;
	t_list_cmd	*list_cmd;

	prev_cmd = smalloc(sizeof(t_cmd));
	prev_cmd->exit_value = 0;
	prev_cmd->mode = AND;
	prev_cmd->cmd = NULL;
	list_cmd = smalloc(sizeof(t_list_cmd));
	list_cmd->next = NULL;
	list_cmd->command = NULL;
	while (*str)
	{
		cmd = init_cmd();
		str = get_next_cmd(str, envp, cmd);
		if (cmd->mode == PIPE)
		{
			while (cmd->mode == PIPE)
			{
				add_back(&list_cmd, cmd);
				cmd = init_cmd();
				str = get_next_cmd(str, envp, cmd);
			}
			print_cmd(list_cmd);
			multiple_cmd(list_cmd, envp);
		}
		if (!cmd->cmd)
		{
			free_t_cmd(cmd);
			return (envp);
		}
		envp = command(cmd, prev_cmd, envp);
		free_t_cmd(prev_cmd);
		prev_cmd = cmd;
	}
	free(str);
	free_t_cmd(prev_cmd);
	exit(EXIT_SUCCESS);
	return (envp);
}

void	start_shell(char **envp, char *str_c)
{
	char	*str;

	while (1)
	{
		if (!str_c)
		{
			printf("exit status = %i\n", g_error);
			str = readline(print_prompt(error_to_color()));
		}
		else
			str = ft_strndup(str_c, ft_strlen(str_c));
		if (!ft_strncmp(str, "exit", 5))
		{
			free(str);
			break ;
		}
		add_history(str);
		if (!check_syntax(str))
			envp = sh(str, envp);
		if (str_c)
			exit (g_error);
	}
}
