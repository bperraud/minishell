/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 01:27:04 by bperraud          #+#    #+#             */
/*   Updated: 2022/06/10 19:37:02 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**update_last_cmd(char **env, t_cmd *cmd)
{
	char	*last_cmd;

	last_cmd = ft_getenv("_", env);
	if (last_cmd)
	{
		env = env_unset("_", env);
		free(last_cmd);
	}
	last_cmd = ft_strjoin("_=", cmd->cmd[0]);
	if (!last_cmd)
		exit(ENOMEM);
	env = env_add(last_cmd, env);
	free(last_cmd);
	return (env);
}

static void	try_exit_and_restore(char *str, char **envp, int fd[2], t_cmd *cmd)
{
	restore_std(fd);
	try_exit(cmd, str, envp);
}

static char	**sh(char *str, char **envp, int fd_save[2], int prev_cmd_mode)
{
	t_cmd	*cmd;

	while (*str && *skip_spaces(str) != '\0')
	{
		cmd = init_cmd(prev_cmd_mode);
		str = get_next_cmd(str, envp, cmd);
		if (!str)
		{
			free_t_cmd(cmd);
			return (envp);
		}
		if (cmd->cmd)
		{
			envp = update_last_cmd(envp, cmd);
			pipe_cmd(&str, envp, fd_save, &cmd);
			envp = command(cmd, fd_save, envp);
			try_exit_and_restore(str, envp, fd_save, cmd);
			prev_cmd_mode = cmd->mode;
			free_t_cmd(cmd);
		}
		else
			here_doc(cmd->here_doc);
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
	if (fd_save[0] < 0 || fd_save[1] < 0)
	{
		error_file_exit("dup");
	}
	if (!g_error)
		prev_cmd_mode = AND;
	else
		prev_cmd_mode = OR;
	return (sh(str, envp, fd_save, prev_cmd_mode));
}

void	start_shell(char **envp, char *str_c)
{
	char	*str;

	term_config();
	while (1)
	{
		if (!str_c)
		{
			sig_handler();
			str = readline(print_prompt(error_to_color()));
			if (!str)
			{
				ft_putstr_fd("exit\n", STDIN);
				exit(g_error);
			}
		}
		else
			str = ft_strndup(str_c, ft_strlen(str_c));
		add_history(str);
		sig_exit();
		if (!check_syntax(str))
			envp = set_up_sh(str, envp);
		if (str_c)
			exit(g_error);
	}
	free_str_list(envp);
}
