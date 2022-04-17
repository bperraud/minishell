/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 15:05:48 by jboumal           #+#    #+#             */
/*   Updated: 2022/04/14 15:05:49 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(char **lst)
{
	int	i;

	if (!lst)
	{
		perror("error");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (*lst)
	{
		printf("%s\n", *lst);
		lst ++;
		i++;
	}
	printf("printed %d elements\n", i);
}
