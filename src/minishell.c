/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 12:19:04 by jboumal           #+#    #+#             */
/*   Updated: 2022/04/08 12:19:06 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sh(char *str)
{
	t_cmd	*cmd;

	cmd = sh_split(str);
	print_list(cmd->cmd);
}

static void	start_shell(void)
{
	char	*str;

	while (1)
	{
		str = readline("\033[36m╰(°▽°)╯~ \033[0m");
		if (!str || !ft_strncmp(str, "exit", 5))
			break ;
		sh(str);
	}
}

int	main(int argc, char **argv)
{
	if (argc == 1)
	{
		start_shell();
	}
	(void) argv;
	//system ("leaks minishell");
	return (0);
}
