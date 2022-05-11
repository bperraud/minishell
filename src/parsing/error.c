/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 13:49:51 by jboumal           #+#    #+#             */
/*   Updated: 2022/05/12 01:28:04 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_cmd_separator(char c)
{
	if (ft_strchr("|&", c))
		return (true);
	else
		return (false);
}

static int	is_unclosed_sentence(int par, char quote)
{
	if (par != 0)
	{
		ft_putstr_fd("minishell: unclosed parenthesis\n", 2);
		g_error = SYNTAX_ERROR;
		return (SYNTAX_ERROR);
	}
	if (quote)
	{
		ft_putstr_fd("minishell: unclosed quote\n", 2);
		g_error = SYNTAX_ERROR;
		return (SYNTAX_ERROR);
	}
	return (0);
}

static int	check_opening_par(t_error *err)
{
	if (!err->is_start_of_cmd)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '('\n", 2);
		g_error = SYNTAX_ERROR;
		return (SYNTAX_ERROR);
	}
	err->par ++;
	return (0);
}

static int	check_closing_par(t_error *err, char **str)
{
	*str = skip_spaces(*str);
	(*str)++;
	if (!is_cmd_separator(**str) || err->is_start_of_cmd)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token ')'\n", 2);
		g_error = SYNTAX_ERROR;
		return (SYNTAX_ERROR);
	}
	err->par--;
	if (err->par < 0)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token ')'\n", 2);
		g_error = SYNTAX_ERROR;
		return (SYNTAX_ERROR);
	}
	err->is_start_of_cmd = true;
	return (0);
}

int	check_syntax(char *str)
{
	t_error	*err;
	int		r_value;

	r_value = 0;
	err = init_error();
	while (*str)
	{
		str = skip_spaces(str);
		if (err->quote)
		{
			if (*str == err->quote)
				err->quote = '\0';
		}
		else if (*str == '\'' || *str == '\"')
			err->quote = *str;
		else if (*str == '(')
		{
			r_value = check_opening_par(err);
			if (r_value != 0)
				return (r_value);
		}
		else if (*str == ')')
		{
			r_value = check_closing_par(err, &str);
			if (r_value != 0)
				return (r_value);
		}
		else if (is_cmd_separator(*str))
			err->is_start_of_cmd = true;
		else
			err->is_start_of_cmd = false;
		str++;
	}
	r_value = is_unclosed_sentence(err->par, err->quote);
	free(err);
	return (r_value);
}
