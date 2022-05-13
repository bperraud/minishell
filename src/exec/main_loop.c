/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 01:27:04 by bperraud          #+#    #+#             */
/*   Updated: 2022/05/13 21:08:06 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**command(t_cmd *cmd, int prev_cmd_mode, char **envp)
{
	if ((prev_cmd_mode == AND && !g_error)
		|| (prev_cmd_mode == OR && g_error))
		return (launch_cmd(cmd, envp));
	return (envp);
}

static void	restore_std(int save_in, int save_out)
{
	dup2(save_in, STDIN);
	dup2(save_out, STDOUT);
}

char	**sh(char *str, char **envp)
{
	t_cmd		*cmd;
	int			save_in;
	int			save_out;
	int			prev_cmd_mode;

	prev_cmd_mode = AND;
	save_in = dup(0);
	save_out = dup(1);
	while (*str)
	{
		cmd = init_cmd();
		str = get_next_cmd(str, envp, cmd);
		if (!str || !cmd->cmd)
		{
			free_t_cmd(cmd);
			return (envp);
		}
		if (cmd->mode == PIPE)
			pipe_cmd(&str, envp, &cmd);
		envp = command(cmd, prev_cmd_mode, envp);
		prev_cmd_mode = cmd->mode;
		restore_std(save_in, save_out);
		try_exit(cmd, str);
	}
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
