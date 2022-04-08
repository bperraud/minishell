/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 18:18:45 by jboumal           #+#    #+#             */
/*   Updated: 2022/01/03 19:33:17 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	c2;
	unsigned char	*t;

	c2 = c;
	t = b;
	while (len > 0)
	{
		*t = c2;
		t++;
		len --;
	}
	return (b);
}
