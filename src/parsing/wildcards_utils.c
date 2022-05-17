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

int	get_nb_star(char *s)
{
	int	i;

	i = 0;
	while (s[i] == '*')
	{
		i++;
	}
	return (i);
}

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

static bool	is_expand(char *str, char *start, char *end)
{
	int	i;
	int	j;

	printf("start:%s ", start);
	printf("end:%s ", end);
	printf("str:%s\n", str);
	if (ft_strlen(str) < ft_strlen(start) + ft_strlen(end))
		return (false);
	i = 0;
	while (start[i])
	{
		if (start[i] != str[i])
			return (false);
		i++;
	}
	i = ft_strlen(str) - ft_strlen(end);
	j = 0;
	while (j < ft_strlen(end))
	{
		if (end[j] == '*')
			return (true);
		if (end[j] != str[i])
			return (false);
		i++;
		j++;
	}
	return (true);
}

char	**get_exp_list(char *start, char *end)
{
	char	**f_list;
	char	**exp_list;
	int		i;

	f_list = init_f_list();
	exp_list = NULL;
	i = 0;
	while (f_list[i])
	{
		if (is_expand(f_list[i], start, end))
			exp_list = add_string(exp_list, ft_strndup(f_list[i], ft_strlen(f_list[i])));
		i++;
	}
	free_str_list(f_list);
	return (exp_list);
}