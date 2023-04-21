/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 22:09:19 by rgomes-c          #+#    #+#             */
/*   Updated: 2022/10/28 19:50:05 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_b(long n, int base)
{
	int		x;

	x = 0;
	if (n < 0)
		x += ft_putchar('-') + ft_putnbr_b(-n, base);
	else if (n > (base - 1))
		x += ft_putnbr_b(n / base, base) + ft_putnbr_b(n % base, base);
	else if (n < 10)
	{
		n = n + 48;
		x += ft_putchar(n);
	}
	else
	{
		n = n + 55;
		x += ft_putchar(n);
	}
	return (x);
}
