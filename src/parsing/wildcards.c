/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:02:13 by jboumal           #+#    #+#             */
/*   Updated: 2022/05/12 14:02:23 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_indir(char *str)
{
	char	**f_list;
	int		i;

	f_list = init_f_list();
	i = 0;
	while (f_list[i])
	{
		if (ft_strcmp(f_list[i], str) == 0)
		{
			free_str_list(f_list);
			return (true);
		}
		i++;
	}
	free_str_list(f_list);
	return (false);
}

bool	is_in_list(char *str, char **lst)
{
	int	i;
	int	len;

	if (!lst)
		return (false);
	len = lst_len(lst);
	i = 0;
	while (i < len)
	{
		if (ft_strcmp(lst[i], str) == 0)
			return (true);
		i++;
	}
	return (false);
}

static bool	remove_duplicates(t_cmd *cmd, int i)
{
	int		len;
	int		j;

	if (!cmd || !cmd->cmd)
		return (false);
	len = lst_len(cmd->cmd);
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strcmp(cmd->cmd[i], cmd->cmd[j]) == 0)
			{
				cmd->cmd = lst_del(cmd->cmd, j);
				return (true);
			}
			j++;
		}
		i++;
	}
	return (false);
}

void	handle_wildcards(t_cmd *cmd)
{
	int		i;
	char	**suffix;
	bool	removed;

	if (!cmd || !cmd->cmd)
		return ;
	i = 0;
	while (cmd->cmd[i])
	{
		if (ft_strchr(cmd->cmd[i], '*'))
		{
			suffix = wildcard_split(cmd->cmd[i]);
			if (!suffix)
				exit(ENOMEM);
			if (expand_wildcards(NULL, suffix, cmd))
			{
				removed = true;
				while (removed)
					removed = remove_duplicates(cmd, i);
				cmd->cmd = lst_del(cmd->cmd, i);
			}
			free_str_list(suffix);
		}
		i++;
	}
}
