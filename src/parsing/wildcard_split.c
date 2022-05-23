/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 17:17:49 by jboumal           #+#    #+#             */
/*   Updated: 2022/05/17 17:17:50 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_word(char *s)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (s[i] == '*')
	{
		n++;
		while (s[i] == '*')
			i++;
	}
	if (!s[i])
		n--;
	while (s[i])
	{
		if (s[i] == '*')
		{
			n++;
			while (s[i] == '*')
				i++;
		}
		i++;
	}
	return (n + 1);
}

static int	len_word(char *s)
{
	int	i;

	i = 0;
	while (*s && *s != '*')
	{
		i++;
		s++;
	}
	return (i);
}

char	**wildcard_split(char *s)
{
	int		i;
	int		nw;
	char	**lst;

	i = 0;
	nw = count_word(s);
	lst = smalloc(nw * sizeof(char *) + 1);
	if (*s == '*')
	{
		lst[0] = ft_strndup("", 0);
		while (*s == '*')
			s++;
		i++;
	}
	while (i < nw)
	{
		if (len_word(s))
		{
			lst[i] = ft_strndup(s, len_word(s));
			s += (len_word(s));
			while (*s == '*')
				s++;
		}
		else
			lst[i] = ft_strndup("", 0);
		i++;
	}
	lst[i] = NULL;
	return (lst);
}