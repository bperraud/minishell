/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 12:19:04 by jboumal           #+#    #+#             */
/*   Updated: 2022/04/25 01:11:49 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	sh(char *str)
{
	t_cmd	*cmd;

	cmd = sh_split(&str);
	while (*str)
	{
		print_list(cmd->cmd);
		print_cmd_args(cmd);
		free_t_cmd(cmd);
		cmd = sh_split(&str);
	}
}

static void	start_shell(void)
{
	char	*str;

	while (1)
	{
		str = readline("\033[33m               __\n              /o_)\n     \
_/\\/\\/\\_/ /\n   _|minishell/\n _|  (  | (  |\n/__.-'|_|--|_| ~ \033[0m");

		if (!str || !ft_strncmp(str, "exit", 5))
		{
			free(str);
			break ;
		}
		sh(str);
		free(str);
	}
}

int	main(int argc, char **argv)
{
	if (argc == 1)
	{
		start_shell();
	}
	(void) argv;
	system ("leaks minishell");
	return (0);
}


/*
int	main(int argc, char **argv, char **envp)
{
	int	fd[3];
	int	exit_status;

	if (argc < 4)
		return (0);
	if (!ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])))
	{
		fd[0] = here_doc(argv[2]);
		fd[1] = open(argv[argc - 1], O_CREAT | O_RDWR | O_APPEND, 0644);
		fd[2] = 3;
		exit_status = multiple_cmd(fd, argc, argv, envp);
		unlink(FILE_NAME);
	}
	else
	{
		fd[0] = open_file(argv[1]);
		fd[1] = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
		fd[2] = 2;
		exit_status = multiple_cmd(fd, argc, argv, envp);
	}
	exit(exit_status);
	//return (0);
}
*/
