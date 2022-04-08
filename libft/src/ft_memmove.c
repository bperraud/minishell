/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:19:08 by jboumal           #+#    #+#             */
/*   Updated: 2022/01/05 12:47:40 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dst2;
	const unsigned char	*src2;

	dst2 = dst;
	src2 = src;
	if (!src && !dst)
		return (dst);
	if (src > dst)
	{
		while (len > 0)
		{
			*dst2++ = *src2++;
			len--;
		}
	}
	else
	{
		while (len > 0)
		{
			*(dst2 + len - 1) = *(src2 + len - 1);
			len--;
		}
	}
	return (dst);
}
