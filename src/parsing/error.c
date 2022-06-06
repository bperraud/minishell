/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 13:49:51 by jboumal           #+#    #+#             */
/*   Updated: 2022/05/31 14:44:53 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_unclosed_sentence(int par, char quote)
{
	if (par != 0)
	{
		ft_putstr_fd("-minishell: unclosed parenthesis\n", 2);
		g_error = SYNTAX_ERROR;
		return (SYNTAX_ERROR);
	}
	if (quote)
	{
		ft_putstr_fd("-minishell: unclosed quote\n", 2);
		g_error = SYNTAX_ERROR;
		return (SYNTAX_ERROR);
	}
	return (0);
}

static int	check_opening_par(t_error *err)
{
	if (!err->is_start_of_cmd)
	{
		ft_putstr_fd("-minishell: syntax error near unexpected token '('\n", 2);
		g_error = SYNTAX_ERROR;
		return (SYNTAX_ERROR);
	}
	err->par ++;
	return (0);
}

static int	check_closing_par(t_error *err, char **str)
{
	(*str)++;
	*str = skip_spaces(*str);
	if ((**str && !ft_strchr("|&)<>", **str)) || err->is_start_of_cmd)
	{
		ft_putstr_fd("-minishell: syntax error near unexpected token ')'\n", 2);
		g_error = SYNTAX_ERROR;
		return (SYNTAX_ERROR);
	}
	err->par--;
	if (err->par < 0)
	{
		ft_putstr_fd("-minishell: syntax error near unexpected token ')'\n", 2);
		g_error = SYNTAX_ERROR;
		return (SYNTAX_ERROR);
	}
	(*str)--;
	return (0);
}

static char	*check_syntax_char(char *str, t_error *err)
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
		if (check_opening_par(err))
			return (NULL);
	}
	else if (*str == ')')
	{
		if (check_closing_par(err, &str))
			return (NULL);
	}
	else if (ft_strchr("|&", *str))
		err->is_start_of_cmd = true;
	else
		err->is_start_of_cmd = false;
	str++;
	return (str);
}

int	check_syntax(char *str)
{
	t_error	*err;
	char	*str_ini;
	char	*save;

	save = str;
	str_ini = str;
	err = init_error();
	if (check_start_and(str) || check_start_or(str))
		return (free_and_return(str_ini, err, 1));
	while (*str || *save)
	{
		str = check_syntax_char(str, err);
		save = check_syntax_operator(save);
		if (!str | !save)
			return (free_and_return(str_ini, err, 1));
	}
	if (is_unclosed_sentence(err->par, err->quote))
		return (free_and_return(str_ini, err, 1));
	return (free_and_return(NULL, err, 0));
}
