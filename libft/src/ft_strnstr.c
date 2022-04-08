/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:06:35 by jboumal           #+#    #+#             */
/*   Updated: 2022/01/11 13:29:04 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*needle)
		return ((char *) haystack);
	if (len <= 0)
		return (NULL);
	i = 0;
	while (haystack[i] && i < len)
	{
		j = 0;
		while (haystack [i + j] == needle [j] && haystack [i + j]
			&& i + j < len)
		{
			if (!haystack [i + j] || j == ft_strlen(needle) - 1)
				return ((char *)(haystack + i));
			j++;
		}
		i ++;
	}
	return (NULL);
}
