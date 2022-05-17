/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 01:27:04 by bperraud          #+#    #+#             */
/*   Updated: 2022/05/17 16:38:17 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	restore_std(int save_in, int save_out)
{
	dup2(save_in, STDIN);
	dup2(save_out, STDOUT);
}

static t_cmd*	first_cmd(void)
{
	t_cmd	*cmd;

	cmd = smalloc(sizeof(t_cmd));
	cmd->mode = AND;
	return (cmd);
}

static char	**sh(char *str, char **envp, int save_in, int save_out)
{
	t_cmd	*cmd;

	cmd = first_cmd();
	while (*str)
	{
		cmd = init_cmd(cmd->mode);
		str = get_next_cmd(str, envp, cmd);
		if (cmd->cmd[0][0] == '(')
			subshell(&cmd, envp);
		else
		{
			if (!str || !cmd->cmd)
			{
				free_t_cmd(cmd);
				return (envp);
			}
			if (cmd->mode == PIPE)
				pipe_cmd(&str, envp, &cmd);
			envp = command(cmd, envp);
			restore_std(save_in, save_out);
			try_exit(cmd, str);
			free_t_cmd(cmd);
		}
	}
	free(str);
	return (envp);
}

static char	**set_up_sh(char *str, char **envp)
{
	int		save_in;
	int		save_out;

	save_in = dup(0);
	save_out = dup(1);
	return (sh(str, envp, save_in, save_out));
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
			envp = set_up_sh(str, envp);
		if (str_c)
			exit (g_error);
	}
}
