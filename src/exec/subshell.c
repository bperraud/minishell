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

void	subshell(t_cmd **cmd, char **envp)
{
	char	**sh;
	int		i;

	sh = malloc(4 * sizeof(char*));
	sh[0] = ft_strdup("./minishell");
	sh[1] = ft_strdup("-c");
	sh[2] = ft_substr((*cmd)->cmd[0], 1, ft_strlen((*cmd)->cmd[0]) - 2);	//pas - 1 ?

	printf("%s\n", sh[2]);
	sh[3] = NULL;
	ft_executable(sh, envp);
	i = 0;
	while(sh[i])
		free(sh[i++]);
	free(sh);
}
