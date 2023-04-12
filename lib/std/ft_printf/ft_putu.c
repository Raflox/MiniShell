/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 22:09:19 by rgomes-c          #+#    #+#             */
/*   Updated: 2022/10/28 22:33:45 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putu(unsigned int n)
{
	int				x;

	x = 0;
	if (n > 9)
	{
		x += ft_putu(n / 10);
		x += ft_putu(n % 10);
	}
	else if (n < 10)
	{
		n = n + 48;
		x += ft_putchar(n);
	}
	else
	{
		n = n + 87;
		x += ft_putchar(n);
	}
	return (x);
}
