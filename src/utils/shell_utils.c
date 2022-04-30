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
