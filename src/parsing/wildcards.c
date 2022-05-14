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

void	expand_wildcards(char *prefix, char *suffix, t_cmd *cmd)
{
	int		i;
	int		j;
	char	*prefix_next;
	char	*suffix_next;
	char	*tmp;
	char	**exp_list;

	int	occ = 0;
	printf("%d: prefix:%s suffix:%s\n", occ++, prefix, suffix);
	if (!prefix) // 1er appel
	{
		i = get_next_star_index(suffix);
		prefix_next = ft_strndup(suffix, i);
		suffix_next = ft_strndup(suffix + i, ft_strlen(suffix) - i);
		free(suffix);
		expand_wildcards(prefix_next, suffix_next, cmd);
	}
	else if (suffix && *suffix) // n-appel
	{	
		i = get_next_star_index(suffix + 1);
		tmp = ft_strndup(suffix + 1, i);
		exp_list = get_exp_list(prefix, tmp);
		j = 0;
		while (exp_list[j])
		{
			prefix_next = ft_strndup(exp_list[j], ft_strlen(exp_list[j]));
			suffix_next = ft_strndup(suffix + i + 1, ft_strlen(suffix) - i - 1);
			expand_wildcards(prefix_next, suffix_next, cmd);
			j++;
		}
		free_str_list(exp_list);
		free(tmp);
		free(suffix);
		free(prefix);
	}
	else // dernier appel
	{
		cmd->cmd = add_string(cmd->cmd, prefix);
	}
}

void	handle_wildcards(t_cmd *cmd)
{
	int		i;
	char	*suffix;

	if (!cmd || !cmd->cmd)
		return ;
	i = 0;
	while (cmd->cmd[i])
	{
		if (ft_strchr(cmd->cmd[i], '*'))
		{
			suffix = ft_strndup(cmd->cmd[i], ft_strlen(cmd->cmd[i]));
			cmd->cmd = lst_del(cmd->cmd, i);
			expand_wildcards(NULL, suffix, cmd);
		}
		i++;
	}
}