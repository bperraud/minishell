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

int	is_cmd_in_path(char *cmd, char **envp)
{
	int		i;
	char	*command;
	char	**paths;
	int		fd;

	i = -1;
	paths = parsing_path(envp);
	while (paths[++i])
	{
		command = create_path(paths[i], cmd);
		fd = open(command, O_RDONLY);
		if (fd != -1)
		{
			free(command);
			free_str_list(paths);
			close(fd);
			return (1);
		}
		free(command);
	}
	free_str_list(paths);
	return (0);
}

char	**parsing_path(char **envp)
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
	char	*buf;

	if (!ft_strlen(limiter))
		return (-1);
	f1 = open(HERE_DOC, O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (1)
	{
		buf = get_next_line(STDIN);
		if (buf && (ft_strlen(buf) - 1 != ft_strlen(limiter)
				|| ft_strncmp(buf, limiter, ft_strlen(limiter)) != 0))
		{
			write(f1, buf, ft_strlen(buf));
			free(buf);
		}
		else
			break ;
	}
	if (buf)
		free(buf);
	close(f1);
	f1 = open(HERE_DOC, O_RDONLY);
	unlink(HERE_DOC);
	return (f1);
}
