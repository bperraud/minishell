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

static bool is_indir(char *str)
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
		if (expand_wildcards(prefix, suffix + 1, cmd))
			replaced = true;
	}
	else if (*suffix && **suffix) // n-appel
	{
		j = 0;
		exp_list = get_exp_list(prefix, suffix[0]);
		if (!exp_list)
		{
			return (false);
		}
		while (exp_list[j])
		{
			 if (expand_wildcards(exp_list[j], suffix + 1, cmd))
			 	replaced = true;
			j++;
		}
		//free_str_list(exp_list);
	}
	else // dernier appel
	{
		if (prefix && *suffix)
		{
			j = 0;
			exp_list = get_exp_list(prefix, suffix[0]);
			if (!exp_list)
				replaced = false;
			while (exp_list[j])
			{
				cmd->cmd = add_string(cmd->cmd, exp_list[j]);
				replaced = true;
				j++;
			}
		}
		else if (prefix)
		{
			if (is_indir(prefix))
			{
				cmd->cmd = add_string(cmd->cmd, prefix);
				replaced = true;
			}
			else
				replaced = false;
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