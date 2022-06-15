/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 11:39:14 by jboumal           #+#    #+#             */
/*   Updated: 2022/06/15 11:22:43 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pwd_cut(void)
{
	char	*pwd;
	char	*tmp;
	int		len;

	tmp = getcwd(NULL, 0);
	len = ft_strlen(tmp);
	pwd = ft_substr(tmp, len - 9, len);
	free(tmp);
	return (pwd);
}

/* His name is dany ; dany loves cookies */
/* Dany is a diplodocus-stegosaurus, a very rare kind of dinosaurus */
char	*print_prompt(char *color)
{
	char	*str;

	str = get_pwd_cut();
	ft_putstr_fd ("               __\n", 1);
	ft_putstr_fd ("              /o_) \n", 1);
	ft_putstr_fd ("     _/\\/\\/\\_/ /   \n", 1);
	ft_putstr_fd ("   _|", 1);
	ft_putstr_fd (color, 1);
	ft_putstr_fd (str, 1);
	ft_putstr_fd (RESET, 1);
	ft_putstr_fd ("/    \n", 1);
	ft_putstr_fd (" _|  (  | (  |     \n", 1);
	free(str);
	return ("/__.-'|_|--|_| ~ ");
}

char	*error_to_color(void)
{
	char	*color;

	if (g_error == 0)
		color = GREEN;
	else
		color = RED;
	return (color);
}

void	prompt_error(char *str, char *error)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
}
