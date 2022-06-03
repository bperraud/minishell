/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 01:27:04 by bperraud          #+#    #+#             */
/*   Updated: 2022/06/03 14:33:02 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**sh(char *str, char **envp, int fd_save[2], int prev_cmd_mode)
{
	t_cmd	*cmd;

	while (*str && *skip_spaces(str) != '\0')
	{
		cmd = init_cmd(prev_cmd_mode);
		str = get_next_cmd(str, envp, cmd);
		if (!str || !cmd->cmd)
		{
			free_t_cmd(cmd);
			return (envp);
		}
		pipe_cmd(&str, envp, &cmd);
		envp = command(cmd, envp);
		restore_std(fd_save);
		try_exit(cmd, str, envp);
		prev_cmd_mode = cmd->mode;
		free_t_cmd(cmd);
	}
	free(str);
	return (envp);
}

static char	**set_up_sh(char *str, char **envp)
{
	int		fd_save[2];
	int		prev_cmd_mode;

	fd_save[0] = dup(STDIN);
	fd_save[1] = dup(STDOUT);
	if (!g_error)
		prev_cmd_mode = AND;
	else
		prev_cmd_mode = OR;
	return (sh(str, envp, fd_save, prev_cmd_mode));
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
			str = readline(print_prompt(error_to_color()));
			if (!str)
				break ;
		}
		else
		{
			//printf("\n");
			str = ft_strndup(str_c, ft_strlen(str_c));
		}
		add_history(str);
		if (!check_syntax(str))
			envp = set_up_sh(str, envp);
		if (str_c)
		{
			free_str_list(envp);
			exit(g_error);
		}
	}
	free_str_list(envp);
}
