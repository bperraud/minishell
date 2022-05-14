/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 12:19:04 by jboumal           #+#    #+#             */
/*   Updated: 2022/05/15 00:36:50 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_error = 0;

void	prompt_error(char* str, char *error)
{
	ft_putstr_fd("-minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
}

int	main(int argc, char **argv, char **envp)
{
	char	**env;

	env = env_dup(envp);
	if (argc == 1)
	{
		start_shell(env, NULL);
	}
	if (argc == 3 && ft_strncmp(argv[1], "-c", 3) == 0)
	{
		start_shell(env, argv[2]);
	}
	return (g_error);
}
