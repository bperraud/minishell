/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:34:55 by bperraud          #+#    #+#             */
/*   Updated: 2022/04/19 23:11:17 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file(char *file)
{
	if (access(file, F_OK) == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (-1);
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
