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

int	test_access(char *str, int file_access)
{
	if (file_access == READ && access(str, F_OK) < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_error = FILE_ERROR;
		return (FILE_ERROR);
	}
	if (file_access == WRITE && access(str, F_OK) == 0 && access(str, W_OK) < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		g_error = FILE_ERROR;
		return (FILE_ERROR);
	}
	else if (file_access == READ && access(str, R_OK) < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		g_error = FILE_ERROR;
		return (FILE_ERROR);
	}
	return (0);
}

int	free_and_return(char *str, void *ptr, int r_value)
{
	if (str)
		free(str);
	free(ptr);
	return (r_value);
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
