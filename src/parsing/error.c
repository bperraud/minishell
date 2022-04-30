/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 13:49:51 by jboumal           #+#    #+#             */
/*   Updated: 2022/04/29 13:49:54 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool is_cmd_separator(char c)
{
	if (ft_strchr("|&", c))
		return (true);
	else
		return (false);
}

bool	check_syntax(char *str)
{
	char	quote;
	int		par;
	bool	is_start_of_cmd;

	quote = '\0';
	par = 0;
	is_start_of_cmd = true;
	while (*str)
	{
		str = skip_spaces(str);
		if (quote)
		{
			if (*str == quote)
				quote = '\0';
		}
		else if (*str == '(')
		{
			if (!is_start_of_cmd)
				return (false);
			par ++;
		}
		else if (*str == ')')
		{
			str = skip_spaces(str);
			str ++;
			if (!is_cmd_separator(*str))
				return (false);
			par --;
			is_start_of_cmd = true;
		}
		else if (is_cmd_separator(*str))
			is_start_of_cmd = true;
		else
			is_start_of_cmd = false;
		str++;
	}
	if (par != 0)
		return (false);
	if (quote)
		return (false);
	return (true);
}