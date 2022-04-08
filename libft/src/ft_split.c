/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 13:15:06 by jboumal           #+#    #+#             */
/*   Updated: 2022/01/07 12:26:10 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	count_word(char const *s, char c)
{
	int	f;
	int	i;

	i = 0;
	f = 1;
	while (*s)
	{
		if (*s != c && f)
		{
			i++;
			f = 0;
		}
		if (*s == c)
			f = 1;
		s++;
	}
	return (i);
}

static int	len_word(const char *s, char c)
{
	int	i;

	i = 0;
	while (*s && *s != c)
	{
		i++;
		s++;
	}
	return (i);
}

static char	**free_all(char **start, char **end)
{
	while (start >= end)
	{
		free(*start);
		start ++;
	}
	free(start);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**t;
	char	**list;
	int		n;

	if (!s)
		return (NULL);
	n = count_word(s, c) + 1;
	list = malloc(sizeof(char *) * n);
	if (!list)
		return (NULL);
	t = list;
	while (--n > 0)
	{
		while (*s && *s == c)
			s++;
		*t = malloc(sizeof(char) * (len_word(s, c) + 1));
		if (!*t)
			return (free_all(list, t - 1));
		ft_strlcpy(*t, s, len_word(s, c) + 1);
		s += len_word(s, c);
		t++;
	}
	*t = NULL;
	return (list);
}
