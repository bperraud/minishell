/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:39:39 by jboumal           #+#    #+#             */
/*   Updated: 2022/01/14 16:40:43 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	intlen(int n)
{
	int	count;

	count = 0;
	if (n < 0)
		count ++;
	while (n)
	{
		count ++;
		n = n / 10;
	}
	return (count);
}

static char	*zero_case(void)
{
	char	*s;

	s = ft_strdup("0");
	return (s);
}

char	*ft_itoa(int n)
{
	char			*s;
	int				len;
	unsigned int	nb;

	len = intlen(n);
	if (len == 0)
		return (zero_case());
	s = malloc (sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	if (n < 0)
	{
		s[0] = '-';
		nb = -n;
	}
	else
		nb = n;
	s[len] = '\0';
	while (nb)
	{
		s[len - 1] = nb % 10 + '0';
		nb = nb / 10;
		len --;
	}
	return (s);
}
