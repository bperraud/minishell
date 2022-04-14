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

void	lstcpy(char **dst, char **src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
}

int	lst_len(char **lst)
{
	int	i;

	if (!lst)
		return (-1);
	i = 0;
	while (lst[i])
		i++;
	return (i);
}

char	**add_string(char **lst1, char *str)
{
	char	**lst2;
	int		len;

	if (lst1)
		len = lst_len(lst1);
	else
		len = 0;
	lst2 = malloc((len + 2) * sizeof(char *));
	if (!lst2)
	{
		perror("error");
		exit(EXIT_FAILURE);
	}
	if (lst1)
	{
		lstcpy(lst2, lst1);
		free(lst1);
	}
	lst2[len] = str;
	lst2[len + 1] = NULL;
	return (lst2);
}

char	*add_char(char *str1, char c)
{
	char	*s2;
	int		len;

	if (str1)
		len = ft_strlen(str1);
	else
		len = 0;
	s2 = malloc((len + 2) * sizeof(char));
	if (!s2)
	{
		perror("error");
		exit(EXIT_FAILURE);
	}
	if (str1)
	{
		ft_strlcpy(s2, str1, len + 1);
		free(str1);
	}
	s2[len] = c;
	s2[len + 1] = '\0';
	return (s2);
}

void	free_str_list(char **list)
{
	char	**t;

	if (!list)
		return ;
	t = list;
	while (*t)
	{
		free(*t);
		t++;
	}
	free(list);
}
