/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 11:39:14 by jboumal           #+#    #+#             */
/*   Updated: 2022/04/29 11:39:15 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* His name is dany ; dany loves cookies */
/* Dany is a diplodocus-stegosaurus, a very rare kind of dinosaurus */
char	*print_prompt(char *color)
{
	if (RL_READLINE_VERSION > 0x800)
	{
		printf ("%s               __  \n", color);
		printf ("              |  | \n");
		printf ("             _|__|_\n");
		printf ("              /o_) \n");
		printf ("     _/\\/\\/\\_/ /   \n");
		printf ("   _|minishell/    \n");
		printf (" _|  (  | (  |     \n");
		return ("/__.-'|_|--|_| ~ " RESET);
	}
	else
	{
		printf ("               __  \n");
		printf ("              |  | \n");
		printf ("             _|__|_\n");
		printf ("              /o_) \n");
		printf ("     _/\\/\\/\\_/ /   \n");
		printf ("   _|minishell/    \n");
		printf (" _|  (  | (  |     \n");
		return ("/__.-'|_|--|_| ~ ");
	}
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
