/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 11:39:14 by jboumal           #+#    #+#             */
/*   Updated: 2022/05/23 04:04:38 by bperraud         ###   ########.fr       */
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

	if (g_error == 0)
		color = GREEN;
	else
		color = RED;
	return (color);
}

void	prompt_error(char *str, char *error)
{
	printf("-minishell: %s: %s", str, error);
}
