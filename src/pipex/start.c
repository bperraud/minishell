/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:25:04 by bperraud          #+#    #+#             */
/*   Updated: 2022/04/25 15:25:04 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	start(int argc, char **argv, char **envp)
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
