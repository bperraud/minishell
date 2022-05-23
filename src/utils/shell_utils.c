/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 16:12:19 by jboumal           #+#    #+#             */
/*   Updated: 2022/05/15 23:37:00 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_directory(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

int	test_access(char *str, int file_access)
{
	if (file_access == READ && access(str, F_OK) < 0)
	{
		prompt_error(str, "No such file or directory\n");
		g_error = FILE_ERROR;
		return (FILE_ERROR);
	}
	if (file_access == WRITE && access(str, F_OK) == 0 && access(str, W_OK) < 0)
	{
		prompt_error(str, "Permission denied\n");
		g_error = FILE_ERROR;
		return (FILE_ERROR);
	}
	else if (file_access == READ && access(str, R_OK) < 0)
	{
		prompt_error(str, "Permission denied\n");
		g_error = NOT_EXECUTABLE;
		return (NOT_EXECUTABLE);
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
		return (SYNTAX_ERROR);
	else
		return (exit_code);
}
