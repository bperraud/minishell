/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:34:55 by bperraud          #+#    #+#             */
/*   Updated: 2022/04/20 00:17:36 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file(char *file)
{
	if (access(file, F_OK) == -1)
	{
		perror("-minishell: ");
		exit (FILE_ERROR);
	}
	return (open(file, O_RDONLY));
}

char	**parsing(char **envp)
{
	int		i;
	char	*str;
	char	**split;

	i = 0;
	while (ft_strncmp(envp[i], "PATH", 4) != 0)
		i++;
	str = ft_substr(envp[i], 5, ft_strlen(envp[i]));
	split = ft_split(str, ':');
	free(str);
	return (split);
}

char	*create_path(char *path, char *arg)
{
	char	*cmd;
	char	*temp;

	temp = ft_strjoin(path, "/");
	cmd = ft_strjoin(temp, arg);
	free(temp);
	return (cmd);
}

int	here_doc(char *limiter)
{
	int		f1;
	size_t	len_limiter;
	char	*buf;

	len_limiter = ft_strlen(limiter);
	f1 = open(HERE_DOC, O_CREAT | O_RDWR | O_TRUNC, 0644);
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
	f1 = open_file(HERE_DOC);
	return (f1);
}
