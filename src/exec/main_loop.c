/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 01:27:04 by bperraud          #+#    #+#             */
/*   Updated: 2022/05/13 00:14:31 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**command(t_cmd *cmd, t_cmd *prev_cmd, char **envp)
{
	if ((prev_cmd->mode == AND && !g_error)
		|| (prev_cmd->mode == OR && g_error))
		return (launch_cmd(cmd, envp));
	return (NULL);
}

static void	restore_std(int save_in, int save_out)
{
	dup2(save_in, STDIN);
	dup2(save_out, STDOUT);
}

static void	pipe_cmd(char **str, char **envp, t_cmd **cmd)
{
	t_list_cmd	*list_cmd;

	list_cmd = init_list();
	while ((*cmd)->mode == PIPE)
	{
		add_back(&list_cmd, *cmd);
		*cmd = init_cmd();
		*str = get_next_cmd(*str, envp, *cmd);
	}
	multiple_cmd(list_cmd, envp);
	free_list_cmd(list_cmd);
}

char	**sh(char *str, char **envp)
{
	t_cmd		*cmd;
	t_cmd		*prev_cmd;
	int			save_in;
	int			save_out;

	prev_cmd = init_cmd();
	prev_cmd->mode = AND;
	save_in = dup(0);
	save_out = dup(1);
	while (*str)
	{
		cmd = init_cmd();
		str = get_next_cmd(str, envp, cmd);
		if (!str || !cmd->cmd)
		{
			free_t_cmd(prev_cmd);
			free_t_cmd(cmd);
			return (envp);
		}
		if (cmd->mode == PIPE)
			pipe_cmd(&str, envp, &cmd);
		envp = command(cmd, prev_cmd, envp);
		free_t_cmd(prev_cmd);
		prev_cmd = cmd;
		restore_std(save_in, save_out);
		try_exit(cmd, prev_cmd, str);
	}
	free_t_cmd(prev_cmd);
	free(str);
	return (envp);
}

void	start_shell(char **envp, char *str_c)
{
	char	*str;

	sig_handler();
	term_config();
	while (1)
	{
		if (!str_c)
		{
			printf("exit status = %i\n", g_error);
			g_error = 0;
			str = readline(print_prompt(error_to_color()));
			if (!str)
				break ;
		}
		else
			str = ft_strndup(str_c, ft_strlen(str_c));
		add_history(str);
		if (!check_syntax(str))
			envp = sh(str, envp);
		if (str_c)
			exit (g_error);
	}
}
