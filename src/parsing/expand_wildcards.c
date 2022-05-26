/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:49:49 by jboumal           #+#    #+#             */
/*   Updated: 2022/05/26 16:49:52 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	first_iteration(char **suffix, t_cmd *cmd, bool replaced)
{
	char	*prefix;

	prefix = suffix[0];
	if (suffix[1])
	{
		if (expand_wildcards(prefix, suffix + 1, cmd))
			replaced = true;
	}
	else
	{
		if (expand_wildcards(prefix, suffix, cmd))
			replaced = true;
	}
	return (replaced);
}

static bool	last_iteration(char *prefix, char **suffix, t_cmd *cmd, bool rep)
{
	int		j;
	char	**exp_list;

	if (prefix && *suffix)
	{
		j = 0;
		exp_list = get_exp_list(prefix, suffix[0]);
		if (!exp_list)
			return (false);
		while (exp_list[j])
		{
			cmd->cmd = add_string(cmd->cmd, ft_sstrdup(exp_list[j]));
			rep = true;
			j++;
		}
		free_str_list(exp_list);
	}
	else if (prefix && is_indir(prefix))
	{
		cmd->cmd = add_string(cmd->cmd, ft_sstrdup(prefix));
		rep = true;
	}
	return (rep);
}

bool	expand_wildcards(char *prefix, char **suffix, t_cmd *cmd)
{
	int		j;
	char	**exp_list;
	bool	replaced;

	replaced = false;
	if (!prefix)
		replaced = first_iteration(suffix, cmd, replaced);
	else if (*suffix && **suffix)
	{
		j = 0;
		exp_list = get_exp_list(prefix, suffix[0]);
		if (!exp_list)
			return (false);
		while (exp_list[j])
		{
			if (expand_wildcards(exp_list[j], suffix + 1, cmd))
				replaced = true;
			j++;
		}
		free_str_list(exp_list);
	}
	else
		replaced = last_iteration(prefix, suffix, cmd, replaced);
	return (replaced);
}
