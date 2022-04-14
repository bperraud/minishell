/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 17:24:49 by jboumal           #+#    #+#             */
/*   Updated: 2022/03/24 17:24:50 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_paths_list(char **envp)
{
	int		i;
	char	**paths;

	i = -1;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "PATH", 4))
			paths = (ft_split(envp[i] + 5, ':'));
	}
	if (!paths)
		exit(EXIT_FAILURE);
	return (paths);
}

char	*get_path(char *cmd, char **envp)
{
	int		i;
	char	*path;
	char	**paths;
	char	*tmp;

	i = -1;
	paths = get_paths_list(envp);
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, X_OK) == 0)
		{
			free_str_list(paths);
			return (path);
		}
	}
	free_str_list(paths);
	return (0);
}
