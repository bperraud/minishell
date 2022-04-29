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
char	*print_prompt(void)
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
