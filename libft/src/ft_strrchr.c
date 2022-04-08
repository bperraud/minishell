/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 16:58:57 by jboumal           #+#    #+#             */
/*   Updated: 2022/01/04 17:26:13 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	c2;
	int		i;

	i = 0;
	while (*s)
	{
		s++;
		i++;
	}
	c2 = c;
	while (i > 0)
	{
		if (*s == c2)
			return ((char *) s);
		s--;
		i--;
	}
	if (*s == c2)
		return ((char *) s);
	return (0);
}
