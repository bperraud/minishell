/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 03:47:33 by bperraud          #+#    #+#             */
/*   Updated: 2022/03/30 03:47:33 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ancien pipex*/
int	pipex(char **cmd, char **envp)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		status;

	if (pipe(pipe_fd) < 0)		// gérer cette erreur
		exit(EXIT_FAILURE);
	pipe(pipe_fd);
	pid = fork();
	if (pid != 0)		// parent
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		waitpid(-1, &status, 0);
	}
	else				// enfant
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		exec_cmd(cmd, envp);
	}
	/*
	if (pid == 0)	// child
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT);
		exec_cmd(cmd, envp);
	}
	else		    // parent
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN);
		waitpid(-1, &status, 0);
	}
	*/
	return (status);
}

int	multiple_cmd(t_list_cmd *list_cmd, char **envp)
{
	int	i;
	int	status;

	//dup_close(fd_in, 0);
	/*
	if (list_cmd->command->fd_in != 0)
		dup_close(list_cmd->command->fd_in, 0);
		*/
	//pipex(list_cmd->command->cmd, envp);
	while (list_cmd)
	{
		//pipex(list_cmd->command->cmd, envp);
		printf("cmd : %s\n", list_cmd->command->cmd[0]);
		pipex(list_cmd->command->cmd, envp);
		if (!list_cmd->next)
		{
			list_cmd = list_cmd->next;
			break;
		}
		list_cmd = list_cmd->next;
	}
	/*
	if (list_cmd->command->fd_out != 1)
		dup_close(fd_out, 1);
		*/
	//close (fd_out)
	// ici output est dans pipe_fd[0]
	/*
	if (!fork())
	{
		if (list_cmd->command->fd_out != 1)
			dup_close(list_cmd->command->fd_out, 1);
		exec_cmd(list_cmd->command->cmd, envp);
	}
	*/
	waitpid(-1, &status, 0);
	return (status);
}

/*
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
*/
