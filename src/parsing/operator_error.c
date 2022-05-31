/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 22:26:21 by bperraud          #+#    #+#             */
/*   Updated: 2022/05/30 22:26:21 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_start_or(char *str)
{
	str = skip_spaces(str);
	if (*str != '|')
		return (0);
	(str)++;
	if (*str && *str == '|')
	{
		ft_putstr_fd("-minishell: syntax error near unexpected token `||'\n", 2);
		g_error = SYNTAX_ERROR;
		return (SYNTAX_ERROR);
	}
	else
	{
		ft_putstr_fd("-minishell: syntax error near unexpected token `|'\n", 2);
		g_error = SYNTAX_ERROR;
		return (SYNTAX_ERROR);
	}
}

int	check_start_and(char *str)
{
	str = skip_spaces(str);
	if (*str != '&')
		return (0);
	(str)++;
	if (*str && *str == '&')
	{
		ft_putstr_fd("-minishell: syntax error near unexpected token `&&'\n", 2);
		g_error = SYNTAX_ERROR;
		return (SYNTAX_ERROR);
	}
	else
	{
		ft_putstr_fd("-minishell: syntax error near unexpected token `&'\n", 2);
		g_error = SYNTAX_ERROR;
		return (SYNTAX_ERROR);
	}
	return (0);
}

/* prev char was '|' */
static int	check_operator_or(char **str)
{
	(*str)++;
	if (**str != '|')
	{
		*str = skip_spaces(*str);
		if (**str && **str == '&')
		{
			(*str)++;
			if (**str == '&')
				ft_putstr_fd("-minishell: syntax error near \
				unexpected token `&&'\n", 2);
			else
				ft_putstr_fd("-minishell: syntax error near \
				unexpected token `&'\n", 2);
			g_error = SYNTAX_ERROR;
			return (SYNTAX_ERROR);
		}
		if (**str && **str == '|')
		{
			ft_putstr_fd("-minishell: syntax error near \
			unexpected token `|'\n", 2);
			g_error = SYNTAX_ERROR;
			return (SYNTAX_ERROR);
		}
	}
	(*str)--;
	return (0);
}

/* prev char was '&' */
static int	check_operator_and(char **str)
{
	(*str)++;
	if (**str != '&')
	{
		*str = skip_spaces(*str);
		if (**str && **str == '|')
		{
			(*str)++;
			if (**str == '|')
				ft_putstr_fd("-minishell: syntax error near \
				unexpected token `||'\n", 2);
			else
				ft_putstr_fd("-minishell: syntax error near \
				unexpected token `|'\n", 2);
			g_error = SYNTAX_ERROR;
			return (SYNTAX_ERROR);
		}
		if (**str && **str == '&')
		{
			ft_putstr_fd("-minishell: syntax error near \
			unexpected token `&'\n", 2);
			g_error = SYNTAX_ERROR;
			return (SYNTAX_ERROR);
		}
	}
	(*str)--;
	return (0);
}

char	*check_syntax_operator(char *str)
{
	str = skip_spaces(str);
	if (*str == '&')
	{
		if (check_operator_and(&str))
			return (NULL);
	}
	else if (*str == '|')
	{
		if (check_operator_or(&str))
			return (NULL);
	}
	str++;
	return (str);
}
