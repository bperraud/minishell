/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 01:25:55 by bperraud          #+#    #+#             */
/*   Updated: 2022/06/05 17:32:04 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	char	*buff;

	g_error = 0;
	buff = getcwd(NULL, 0);
	ft_putstr_fd(buff, 1);
	ft_putstr_fd("\n", 1);
	free(buff);
}
