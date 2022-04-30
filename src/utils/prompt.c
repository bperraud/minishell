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
	printf (GREEN "               __  "    RESET "\n");
	printf (GREEN "              |  | "    RESET "\n");
	printf (GREEN "             _|__|_"    RESET "\n");
	printf (GREEN "              /o_) "    RESET "\n");
	printf (GREEN "     _/\\/\\/\\_/ /   " RESET "\n");
	printf (GREEN "   _|minishell/    "    RESET "\n");
	printf (GREEN " _|  (  | (  |     "    RESET "\n");
	printf("version=%x\n",RL_READLINE_VERSION);
	return (GREEN "/__.-'|_|--|_| ~ "      RESET);
}