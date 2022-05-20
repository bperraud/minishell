/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:05:11 by jboumal           #+#    #+#             */
/*   Updated: 2022/05/20 21:12:13 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**unset(char *var, char **env)
{
	if (!ft_getenv(var, env))
		return (env);
	return (env_unset(var, env));
}
