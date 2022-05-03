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

static bool	is_cmd_separator(char c)
{
	if (ft_strchr("|&", c))
		return (true);
	else
		return (false);
}

static void	check_unclosed_sentence(int par, char quote)
{
	if (par != 0)
	{
		ft_putstr_fd("minishell: unclosed parenthesis\n", 2);
		exit (SYNTAX_ERROR);
	}
	if (quote)
	{
		ft_putstr_fd("minishell: unclosed quote\n", 2);
		exit (SYNTAX_ERROR);
	}
}

static void	check_opening_par(t_error *err)
{
	if (!err->is_start_of_cmd)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '('\n", 2);
		exit (SYNTAX_ERROR);
	}
	err->par ++;
}

static void	check_closing_par(t_error *err, char **str)
{
	*str = skip_spaces(*str);
	(*str)++;
	if (!is_cmd_separator(**str) || err->is_start_of_cmd)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token ')'\n", 2);
		exit (SYNTAX_ERROR);
	}
	err->par--;
	if (err->par < 0)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token ')'\n", 2);
		exit (SYNTAX_ERROR);
	}
	err->is_start_of_cmd = true;
}

void	check_syntax(char *str)
{
	t_error	*err;

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
			check_opening_par(err);
		else if (*str == ')')
			check_closing_par(err, &str);
		else if (is_cmd_separator(*str))
			err->is_start_of_cmd = true;
		else
			err->is_start_of_cmd = false;
		str++;
	}
	check_unclosed_sentence(err->par, err->quote);
	free(err);
}
