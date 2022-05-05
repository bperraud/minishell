/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 12:19:04 by jboumal           #+#    #+#             */
/*   Updated: 2022/04/28 19:58:21 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_error = 0;

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
	system ("leaks minishell");
	return (0);
}
