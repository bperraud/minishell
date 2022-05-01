/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 00:31:59 by bperraud          #+#    #+#             */
/*   Updated: 2022/05/01 00:31:59 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_putnbr_count(long long int nb, const char *base)
{
	if (nb < 0)
	{
		write(1, "-", 1);
		return (1 + ft_putnbr_count(-nb, base));
	}
	if (nb >= (long long int)ft_strlen(base))
		return (ft_putnbr_count(nb / ft_strlen(base), base)
			+ write(1, &base[nb % ft_strlen(base)], 1));
	return (write(1, &base[nb % ft_strlen(base)], 1));
}

int	ft_putaddress_count(unsigned long long int nb)
{
	char	*base;

	base = "0123456789abcdef";
	if (nb >= (unsigned long long int)ft_strlen(base))
		return (ft_putnbr_count(nb / ft_strlen(base), base)
			+ write(1, &base[nb % ft_strlen(base)], 1));
	return (write(1, &base[nb % ft_strlen(base)], 1));
}

int	ft_format(char c, va_list args)
{
	char	*str;
	char	x;

	if (c == 'c')
	{
		x = va_arg(args, int);
		return (write(1, &x, 1));
	}
	if (c == 'd' || c == 'i')
		return (ft_putnbr_count(va_arg(args, int), "0123456789"));
	if (c == 'u')
		return (ft_putnbr_count(va_arg(args, unsigned), "0123456789"));
	if (c == 'x')
		return (ft_putnbr_count(va_arg(args, unsigned), "0123456789abcdef"));
	if (c == 'X')
		return (ft_putnbr_count(va_arg(args, unsigned), "0123456789ABCDEF"));
	if (c == 'p')
		return (write (1, "0x", 2)
			+ ft_putaddress_count(va_arg(args, unsigned long long int)));
	str = va_arg(args, char *);
	if (!str)
		return (write(1, "(null)", 6));
	return (write(1, str, ft_strlen(str)));
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		o_len;

	va_start(args, str);
	o_len = 0;
	while (*str)
	{
		if (*str == '%' && *(++str) != '%')
		{
			o_len += ft_format(*(str++), args);
			continue ;
		}
		write(1, str++, 1);
		o_len++;
	}
	va_end(args);
	return (o_len);
}
