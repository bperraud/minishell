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

void	check_syntax(char *str)
{
	char	quote;
	//int		par;

	quote = '\0';
	str = skip_spaces(str);
	while (*str)
	{
		if (quote)
		{
			if (*str == quote)
				quote = '\0';
		}
		str++;
	}
}