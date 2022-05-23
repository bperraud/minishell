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

static bool	expand_wildcards(char *prefix, char **suffix, t_cmd *cmd)
{
	int		j;
	char	**exp_list;
	bool	replaced;

	replaced = false;
	static int	occ = 0;
	printf("%d: prefix:%s suffix[0]:%s, %d\n", occ++, prefix, *suffix, prefix && *suffix && **suffix);
	if (!prefix) //premier appel
	{
		prefix = suffix[0];
		expand_wildcards(prefix, suffix + 1, cmd);
	}
	else if (*suffix && **suffix) // n-appel
	{
		j = 0;
		exp_list = get_exp_list(prefix, suffix[0]);
		while (exp_list && exp_list[j])
		{
			replaced = expand_wildcards(exp_list[j], suffix + 1, cmd);
			j++;
		}
		if (!exp_list)
		{
			replaced = expand_wildcards(NULL, NULL, cmd);
		}
		free_str_list(exp_list);
	}
	else // dernier appel
	{
		if (prefix)
		{
			cmd->cmd = add_string(cmd->cmd, prefix);
			replaced = true;
		}
	}
	return (replaced);
}

void	handle_wildcards(t_cmd *cmd)
{
	int		i;
	char	**suffix;

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
				cmd->cmd = lst_del(cmd->cmd, i);
			free_str_list(suffix);
		}
		i++;
	}
}