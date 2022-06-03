/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:34:06 by bperraud          #+#    #+#             */
/*   Updated: 2022/05/16 14:34:06 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *cmd_join(t_cmd *command)
{
	int		argc;
	char	*tmp;
	int		i;
	char	*join_cmd;

	argc = 0;
	while (command->cmd[argc + 1])
		argc++;
	join_cmd = ft_sstrdup(command->cmd[0]);
	i = 1;
	while (command->cmd[i])
	{
		tmp = ft_strjoin(join_cmd, " ");
		free(join_cmd);
		join_cmd = ft_strjoin(tmp, command->cmd[i]);
		free(tmp);
		i++;
	}
	return (join_cmd);
}

void	subshell(t_cmd *command, char **envp)
{
	char	**sh;
	char	*pwd;
	char	*full_path;

	pwd = ft_getenv("PWD", envp);
	full_path = ft_strjoin(pwd, "/minishell");
	free(pwd);
	sh = smalloc(4 * sizeof(char *));
	sh[0] = ft_sstrdup(full_path);
	sh[1] = ft_sstrdup("-c");
	if (command->cmd[0][0] == '(')
		sh[2] = ft_strndup(command->cmd[0] + 1, ft_strlen(command->cmd[0]) - 2);
	else
		sh[2] = cmd_join(command);
	sh[3] = NULL;
	ft_executable(sh, envp);
	free(full_path);
	free_str_list(sh);
}


/*
void	subshell_pipe(t_cmd *command, char **envp)
{
	char	**sh;

	sh = smalloc(4 * sizeof(char *));
	sh[0] = ft_sstrdup("./minishell");
	sh[1] = ft_sstrdup("-c");
	sh[2] = ft_sstrdup(command->cmd[0]);
	sh[3] = NULL;



	ft_executable(sh, envp);
	free_str_list(sh);
}

void	subshell(t_cmd *cmd, char **envp)
{
	char	**sh;
	char	*pwd;
	char	*full_path;

	pwd = ft_getenv("PWD", envp);
	full_path = ft_strjoin(pwd, "/minishell");
	free(pwd);
	sh = smalloc(4 * sizeof(char *));
	sh[0] = ft_sstrdup(full_path);
	sh[1] = ft_sstrdup("-c");
	sh[2] = ft_strndup(cmd->cmd[0] + 1, ft_strlen(cmd->cmd[0]) - 2);
	sh[3] = NULL;
	ft_executable(sh, envp);
	free(full_path);
	free_str_list(sh);
}
*/
