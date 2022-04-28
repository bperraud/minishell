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

/* ancien pipex pas utilisé */
int	pipex(char **cmd, char**envp)
{
	int		pid;
	int		pipe_fd[2];
	int		status;

	if (pipe(pipe_fd) < 0)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid)	// parent
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		waitpid(-1, &status, 0);
	}
	else
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		exec_cmd(cmd, envp);
	}
	return (status);
}

/* redirect to appropriate function for a cmd */
void	which_cmd(char **cmd, char **envp)
{
	if (!ft_strcmp(cmd[0], "cd"))
	{
		//chdir()
		;
	}
	else
		pipex(cmd, envp);
}

int	cmd_pipe(t_cmd *command, char **envp)
{
	if (command->fd_in != 0)	// lire l'entrée dans fd_in
		dup_close(command->fd_in, 0);
	if (command->fd_out != 1)	// rediriger la sortie vers fd_out
		dup_close(command->fd_out, 1);
}

/*
int	multiple_cmd(int fd[3], int argc, char **argv, char **envp)
{
	int	fd_in;
	int	fd_out;
	int	i;
	int	status;

	fd_in = fd[0];
	fd_out = fd[1];
	i = fd[2];

	dup_close(fd_in, 0);
	pipex(argv[i], envp);
	while (++i < argc - 2)
		pipex(argv[i], envp);
	//dup_close(fd_out, 1);
	close(fd_out);
	// ici output est dans pipe_fd[0]
	if (!fork())
		exec_cmd(argv[argc - 2], envp);
	return (status);
}

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
