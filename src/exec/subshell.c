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

void	subshell_pipe(t_cmd *command, char **envp)
{
	char	**sh;
	int		i;
	int		argc;
	char	*tmp;

	argc = 0;
	while (command->cmd[argc + 1])
		argc++;
	sh = smalloc((argc + 4) * sizeof(char *));
	sh[0] = ft_sstrdup("./minishell");
	sh[1] = ft_sstrdup("-c");
	sh[2] = ft_sstrdup(command->cmd[0]);
	sh[3] = NULL;
	i = 1;
	while (command->cmd[i])
	{
		tmp = ft_strjoin(sh[2], " ");
		sh[2] = ft_strjoin(tmp, command->cmd[i]);
		free(tmp);
		i++;
	}
	ft_executable(sh, envp);
	free_str_list(sh);
}

void	subshell(t_cmd *cmd, char **envp)
{
	char	**sh;

	sh = smalloc(4 * sizeof(char *));
	sh[0] = ft_sstrdup("./minishell");
	sh[1] = ft_sstrdup("-c");
	sh[2] = ft_strndup(cmd->cmd[0] + 1, ft_strlen(cmd->cmd[0]) - 2);
	sh[3] = NULL;
	ft_executable(sh, envp);
	free_str_list(sh);
}
