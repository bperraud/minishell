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

# include "minishell.h"

void	subshell(char **str, char **envp, t_cmd **cmd)
{
	//char	*parentheses;

	(*cmd)->cmd[0] = ft_substr((*cmd)->cmd[0], 1, ft_strlen((*cmd)->cmd[0]));
	printf("str1: %s\n", str);
	while ((*cmd)->cmd[ft_strlen((*cmd)->cmd)][ft_strlen((*cmd)->cmd)] != ')')
	{
		//str = ft_strjoin(str, (*cmd)->cmd);
		*cmd = init_cmd(AND);
		*str = get_next_cmd(*str, envp, *cmd);
		printf("cmd : %s\n", (*cmd)->cmd[0]);
	}
}
