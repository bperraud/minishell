/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:40:34 by jboumal           #+#    #+#             */
/*   Updated: 2022/04/13 11:40:36 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(char *src, int n)
{
	char	*dst;

	dst = smalloc ((n + 1) * sizeof(char));
	ft_strlcpy(dst, src, n + 1);
	return (dst);
}

void	*smalloc(size_t n_bytes)
{
	void	*data;

	data = malloc (n_bytes);
	if (!data)
	{
		perror("minishell");
		exit(ENOMEM);
	}
	return (data);
}

char	**add_string(char **lst1, char *str)
{
	char	**lst2;
	int		len;

	if (!str)
		return (lst1);
	if (lst1)
		len = lst_len(lst1);
	else
		len = 0;
	lst2 = smalloc((len + 2) * sizeof(char *));
	if (lst1)
	{
		lstcpy(lst2, lst1);
		free(lst1);
	}
	lst2[len] = str;
	lst2[len + 1] = NULL;
	return (lst2);
}

char	*add_multiple_chars(char *s1, char *s2)
{
	if (!s2)
		return (s1);
	while (*s2)
	{
		s1 = add_char(s1, *s2);
		s2++;
	}
	return (s1);
}

char	*add_char(char *str1, char c)
{
	char	*s2;
	int		len;

	if (str1)
		len = ft_strlen(str1);
	else
		len = 0;
	s2 = smalloc((len + 2) * sizeof(char));
	if (str1)
	{
		ft_strlcpy(s2, str1, len + 1);
		free(str1);
	}
	s2[len] = c;
	s2[len + 1] = '\0';
	return (s2);
}
