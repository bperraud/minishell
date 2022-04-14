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

void	sh(t_cmd *cmd)
{
	(void) cmd;
}

static void	start_shell(void)
{
	char	*str;
	t_cmd	*cmd;

	while (1)
	{
		str = readline("\033[36m╰(°▽°)╯~ \033[0m");
		if (!str || !ft_strncmp(str, "exit", 5))
			break ;
		cmd = parse_cmd(str);
		//execute the command
		//free cmd
		printf("%s\n", str);
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
