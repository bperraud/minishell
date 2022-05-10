/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 20:32:22 by jboumal           #+#    #+#             */
/*   Updated: 2022/05/03 20:32:23 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lstcpy(char **dst, char **src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
}

int	lst_len(char **lst)
{
	int	i;

	if (!lst)
		return (0);
	i = 0;
	while (lst[i])
		i++;
	return (i);
}
