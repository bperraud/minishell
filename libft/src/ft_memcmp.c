/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 13:41:39 by jboumal           #+#    #+#             */
/*   Updated: 2022/01/05 13:58:14 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ts1;
	const unsigned char	*ts2;

	ts1 = s1;
	ts2 = s2;
	while (n > 0 && (*ts1 == *ts2))
	{
		ts1++;
		ts2++;
		n--;
	}
	if (n == 0)
		return (0);
	return ((unsigned char)*ts1 - (unsigned char)*ts2);
}
