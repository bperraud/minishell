/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:16:07 by jboumal           #+#    #+#             */
/*   Updated: 2022/01/07 13:08:14 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	isin(char c, const char *s)
{
	while (*s)
	{
		if (c == *s)
			return (1);
		s++;
	}
	return (0);
}

static char	*empty_string(void)
{
	char	*s;

	s = malloc(sizeof(char));
	if (!s)
		return (NULL);
	*s = '\0';
	return (s);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char const	*t;
	char		*s;
	int			size;

	if (!s1 || !set)
		return (NULL);
	size = 0;
	while (*s1 && isin(*s1, set))
		s1++;
	if (!*s1)
		return (empty_string());
	t = s1 - 1;
	while (*++t)
		size ++;
	t--;
	while (isin(*t, set) && size--)
		t--;
	s = malloc(sizeof(char) * (size + 1));
	if (!s)
		return (NULL);
	ft_strlcpy(s, s1, size + 1);
	return (s);
}
