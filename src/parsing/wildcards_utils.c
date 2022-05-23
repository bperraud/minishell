/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 13:36:44 by jboumal           #+#    #+#             */
/*   Updated: 2022/05/14 13:37:21 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**lst_del(char **lst, int n)
{
	int		i;
	int		j;
	int		len;
	char	**new_lst;

	if (!lst)
		return (NULL);
	len = lst_len(lst);
	new_lst = smalloc (len * sizeof(char*));
	i = 0;
	j = 0;
	while (lst[i])
	{
		if (i != n)
		{
			new_lst[j] = ft_strndup(lst[i], ft_strlen(lst[i]));
			i++;
			j++;
		}
		else
		{
			//free(lst[i]);
			i++;
		}
	}
	new_lst[j] = NULL;
	free_str_list(lst);
	return (new_lst);
}

int	get_next_star_index(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			return (i);
		i++;
	}
	return (i);
}

static char	**init_f_list(void)
{
	DIR				*d;
	struct dirent	*dir;
	char			**lst;

	lst = NULL;
	d = opendir(".");
	if (d)
	{
		dir = readdir(d);
		while (dir != NULL)
		{
			lst = add_string(lst, ft_strndup(dir->d_name, ft_strlen(dir->d_name)));
			//free(dir);
			dir = readdir(d);
		}
		closedir(d);
	}
	return(lst);
}

static char	*get_expand(char *str, char *start, char *next)
{
	int		i;

	i = 0;
	while (start[i]) //boucle sur le debut
	{
		if (str[i] != start[i])
			return (NULL);
		i++;
	}
	if (!*next)
		return (ft_strndup(str, ft_strlen(str)));
	while (i < ft_strlen(str)) //boucle sur fin de str
	{
		if (strcmp(str + i, next) == 0)
		{
			return (ft_strndup(str, i + ft_strlen(next)));
		}
		i++;
	}
	return (NULL);
}

char	**get_exp_list(char *start, char *end)
{
	char	**f_list;
	char	**exp_list;
	int		i;
	char	*str;

	f_list = init_f_list();
	exp_list = NULL;
	i = 0;
	while (f_list[i])
	{
		str = get_expand(f_list[i], start, end);
		printf("adding str: %s start: %s end: %s\n", str, start, end);
		if (str)
		{
			exp_list = add_string(exp_list, str);
		}
		i++;
	}
	free_str_list(f_list);
	return (exp_list);
}
