/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:07:49 by jboumal           #+#    #+#             */
/*   Updated: 2022/05/24 16:15:26 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_var_len(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (ft_isdigit(*s) || *s == '?')
		return (1);
	while (s[i] && (ft_isdigit(s[i]) || ft_isalpha(s[i]) || s[i] == '_'))
	{
		i++;
	}
	return (i);
}
