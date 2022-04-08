/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 13:15:15 by jboumal           #+#    #+#             */
/*   Updated: 2022/01/07 14:20:22 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	write_s(char *s, int size, int fd)
{
	int	i;

	i = size;
	while (i <= 9)
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	change_negative_number(int d, int fd)
{
	if (d < 0)
	{
		d = -d;
		write(fd, "-", 1);
	}
	return (d);
}

void	ft_putnbr_fd(int n, int fd)
{
	int		count;
	char	c;
	char	s[10];

	count = 0;
	if (n == 0)
		write(fd, "0", 1);
	else if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		n = change_negative_number(n, fd);
		while (n != 0)
		{
			c = n % 10 + '0';
			n = n / 10;
			s [9 - count] = c;
			count ++;
		}
		write_s(s, 10 - count, fd);
	}
}
