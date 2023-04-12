/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 22:09:19 by rgomes-c          #+#    #+#             */
/*   Updated: 2022/10/28 12:01:49 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putptr_hex(unsigned long nb)
{
	int		x;

	x = 0;
	if (nb > 15)
	{
		x += ft_putptr_hex(nb / 16);
		x += ft_putptr_hex(nb % 16);
	}
	else if (nb < 10)
	{
		nb = nb + 48;
		x += ft_putchar(nb);
	}
	else
	{
		nb = nb + 87;
		x += ft_putchar(nb);
	}
	return (x);
}

int	ft_putptr(unsigned long n)
{
	if (!n)
		return (ft_putstr("(nil)"));
	return (ft_putstr("0x") + ft_putptr_hex(n));
}
