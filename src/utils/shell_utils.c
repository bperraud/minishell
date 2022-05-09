/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 16:12:19 by jboumal           #+#    #+#             */
/*   Updated: 2022/04/30 16:12:20 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_var_len(char *s)
{
	int	i;

	i = 0;
	if (ft_isdigit(*s) || *s == '?')
		return (1);
	while (s[i] && (ft_isdigit(s[i]) || ft_isalpha(s[i]) || s[i] == '_'))
	{
		i++;
	}
	return (i);
}

void	test_access(char *str, int file_access)
{
	if (access(str, F_OK) < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(FILE_ERROR);
	}
	if (file_access == WRITE && access(str, W_OK) < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		exit(FILE_ERROR);
	}
	else if (file_access == READ && access(str, R_OK) < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		exit(FILE_ERROR);
	}
}

char	*skip_spaces(char *str)
{
	while (*str == ' ')
		(str ++);
	return (str);
}

int	exit_to_bash_code(int exit_code)
{
	if (exit_code == 2)
		return (258);
	else
		return (exit_code);
}
