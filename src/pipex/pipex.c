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

void	exec_cmd(char *arg, char **envp)
{
	int		i;
	char	*cmd;
	char	**paths;
	char	**cmd_arg;

	paths = parsing(envp);
	cmd_arg = split_arg(arg, ' ');
	i = -1;
	while (paths[++i])
	{
		cmd = create_path(paths[i], cmd_arg[0]);
		if (!cmd)
		{
			free_tab(cmd_arg);
			free_tab(paths);
			return ;
		}
		execve(cmd, cmd_arg, envp);
		free(cmd);
	}
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(cmd_arg[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(128);
}

int	here_doc(char *limiter)
{
	int		f1;
	size_t	len_limiter;
	char	*buf;

	len_limiter = ft_strlen(limiter);
	f1 = open(FILE_NAME, O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (1)
	{
		write(STDIN_FILENO, "> ", 2);
		buf = get_next_line(1);
		if (buf && (ft_strlen(buf) - 1 != len_limiter
				|| ft_strncmp(buf, limiter, len_limiter) != 0))
			write(f1, buf, ft_strlen(buf));
		else
			break ;
	}
	close(f1);
	f1 = open_file(FILE_NAME);
	return (f1);
}

void	pipex(char *cmd, char**envp)
{
	int		pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
	}
	else
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		exec_cmd(cmd, envp);
	}
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
	dup2(fd_in, 0);
	close(fd_in);
	pipex(argv[i], envp);
	while (++i < argc - 2)
		pipex(argv[i], envp);
	while (waitpid(-1, &status, 0) > 0)
		;
	dup2(fd_out, 1);
	close(fd_out);
	if (!fork())
		exec_cmd(argv[argc - 2], envp);
	return (status);
}
