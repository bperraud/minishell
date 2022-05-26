/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:07:49 by jboumal           #+#    #+#             */
/*   Updated: 2022/05/26 14:10:04 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	correct_env_variable(char *cmd)
{
	if (cmd[0] == '=' || cmd[0] == '?' || ft_isdigit(cmd[0])
		|| !ft_strchr(cmd, '='))
		return (0);
	return (1);
}

int	get_var_len(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (ft_isdigit(*s) || *s == '?')
		return (1);
	while (s[i] && (ft_isdigit(s[i]) || ft_isalpha(s[i]) || s[i] == '_'))
	{
		i++;
	}
	return (i);
}
