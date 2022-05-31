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

int	subshell(t_cmd **cmd, char **envp)
{
	char	**sh;
	int		cmd_mode;

	if (((*cmd)->prev_cmd == AND && g_error)
		|| ((*cmd)->prev_cmd == OR && !g_error))
		return (cmd_mode);
	sh = smalloc(4 * sizeof(char *));
	sh[0] = ft_sstrdup("./minishell");
	sh[1] = ft_sstrdup("-c");
	sh[2] = ft_strndup((*cmd)->cmd[0] + 1, ft_strlen((*cmd)->cmd[0]) - 2);
	sh[3] = NULL;
	cmd_mode = (*cmd)->mode;
	ft_executable(sh, envp);
	free_str_list(sh);
	free_t_cmd(*cmd);
	return (cmd_mode);
}
