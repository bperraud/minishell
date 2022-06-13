/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:40:34 by jboumal           #+#    #+#             */
/*   Updated: 2022/06/13 17:27:30 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*skip_quotation_marks(char *str)
{
	if (*str == '\'')
	{
		str++;
		while (*str != '\'' && *str)
		{
			str++;
		}
	}
	else if (*str == '\"')
	{
		str++;
		while (*str != '\"' && str)
		{
			str++;
		}
	}
	return (str);
}

char	**update_pwd(char **env)
{
	char	*path;
	char	*var;

	env = try_unset("PWD", env);
	path = getcwd(NULL, 0);
	var = ft_sstrdup("PWD=");
	var = add_multiple_chars(var, path);
	env = env_add(var, env);
	free(var);
	free(path);
	return (env);
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
