/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:35:44 by jboumal           #+#    #+#             */
/*   Updated: 2022/01/05 18:46:46 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size;
	char	*s3;
	char	*t;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	s3 = malloc(sizeof(char) * (size + 1));
	if (!s3)
		return (NULL);
	t = s3;
	while (*s1)
	{
		*t = *s1;
		t++;
		s1++;
	}
	while (*s2)
	{
		*t = *s2;
		t++;
		s2++;
	}
	*t = '\0';
	return (s3);
}
