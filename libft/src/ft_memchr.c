/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 13:10:41 by jboumal           #+#    #+#             */
/*   Updated: 2022/01/05 17:35:19 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		c2;
	const unsigned char	*s2;

	s2 = s;
	c2 = c;
	while (n > 0)
	{
		if (*s2 == c2)
			return ((char *) s2);
		s2++;
		n--;
	}
	return (0);
}
