/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 12:15:04 by jboumal           #+#    #+#             */
/*   Updated: 2022/06/13 23:36:07 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_operators_in_a_row(char *str)
{
	int		and_op;
	int		or_op;

	and_op = 0;
	or_op = 0;
	while (*str == '&')
	{
		and_op++;
		str++;
	}
	while (*str++ == '|')
		or_op++;
	if (or_op < 3 && and_op < 3)
		return (0);
	if (and_op == 3)
		ft_putstr_fd("minishell: syntax error near unexpected token `&'\n", 2);
	if (and_op > 3)
		ft_putstr_fd("minishell: syntax error near unexpected token `&&'\n", 2);
	if (or_op == 3)
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	if (or_op > 3)
		ft_putstr_fd("minishell: syntax error near unexpected token `||'\n", 2);
	return (1);
}

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
