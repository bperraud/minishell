/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 16:56:49 by jboumal           #+#    #+#             */
/*   Updated: 2022/01/14 16:41:07 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_atoi(const char *str)
{
	long	nb;
	int		negative;

	nb = 0;
	negative = 1;
	while (*str == ' ' || *str == '\f' || *str == '\n'
		|| *str == '\r' || *str == '\t' || *str == '\v')
		str ++;
	if (*str == '-')
	{
		negative = -1;
		str ++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nb = nb * 10 + *str - '0';
		if (nb > 2147483647 && negative == 1)
			return (0);
		if (nb > 2147483648 && negative == -1)
			return (-1);
		str ++;
	}
	return (negative * nb);
}
