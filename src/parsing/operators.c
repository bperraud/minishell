/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 12:15:04 by jboumal           #+#    #+#             */
/*   Updated: 2022/04/21 12:15:06 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_operator(t_cmd *cmd, char *s)
{
	while (*s == ' ')
		s++;
	if (*s == '|')
	{
		s++;
		if (*s == '|')
		{
			cmd->mode = OR;
			s++;
		}
		else
			cmd->mode = PIPE;
	}
	else if (*s == '&')
	{
		s += 2;
		cmd->mode = AND;
	}
	return (s);
}
