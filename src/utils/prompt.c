/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 11:39:14 by jboumal           #+#    #+#             */
/*   Updated: 2022/06/05 20:20:20 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* His name is dany ; dany loves cookies */
/* Dany is a diplodocus-stegosaurus, a very rare kind of dinosaurus */
char	*print_prompt(char *color)
{
	ft_putstr_fd (color, 1);
	ft_putstr_fd ("               __  \n", 1);
	ft_putstr_fd ("              |  | \n", 1);
	ft_putstr_fd ("             _|__|_\n", 1);
	ft_putstr_fd ("              /o_) \n", 1);
	ft_putstr_fd ("     _/\\/\\/\\_/ /   \n", 1);
	ft_putstr_fd ("   _|minishell/    \n", 1);
	ft_putstr_fd (" _|  (  | (  |     \n", 1);
	return ("/__.-'|_|--|_| ~ " RESET);
}

char	*error_to_color(void)
{
	char	*color;

	if (g_error == 0 || g_error == OR_MODE_ERROR)
		color = GREEN;
	else
		color = RED;
	return (color);
}

void	prompt_error(char *str, char *error)
{
	ft_putstr_fd("-minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
}
