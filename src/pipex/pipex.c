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

int		pipex(char *cmd, char**envp)
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

int		pipex_minishell(char **cmd, char**envp)
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
		exec_cmd_minishell(cmd, envp);
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
		pipex_minishell(cmd, envp);
}

int	cmd_pipex(t_cmd *command, char **envp)
{
	// note : après pipex : résultat tj dans fd = 0

	int	status;
	int	pid;

	if (command->fd_out != 0)	// rediriger la sortie vers fd_out
	{
		dup_close(command->fd_out, 1);
		//pid = fork();
		if (!fork())
			exec_cmd_minishell(command->cmd, envp);
		waitpid(-1, &status, 0);
		return (status);
	}
	if (command->fd_in != 0)		// lire l'entrée dans fd_in
		dup_close(command->fd_in, 0);

	return (pipex_minishell(command->cmd, envp));
}

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

	//build_in(argv[i], envp);
	pipex(argv[i], envp);
	while (++i < argc - 2)
		pipex(argv[i], envp);


	dup_close(fd_out, 1);


	if (!fork())
		exec_cmd(argv[argc - 2], envp);

	return (status);
}
