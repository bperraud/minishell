/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 17:29:49 by jboumal           #+#    #+#             */
/*   Updated: 2022/01/05 17:32:58 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*s;
	char	*dup;
	int		size;

	size = 0;
	s = (char *) src;
	while (*s++)
		size ++;
	dup = malloc((size + 1) * sizeof(char));
	if (!dup)
		return (0);
	s = dup;
	while (*src)
	{
		*s = *src;
		src ++;
		s ++;
	}
	*s = '\0';
	return (dup);
}
