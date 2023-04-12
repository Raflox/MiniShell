/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:11:45 by rgomes-c          #+#    #+#             */
/*   Updated: 2022/11/16 15:11:56 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_char_in_conditions(char c, va_list *args)
{
	if (c == 'c')
		return (ft_putchar(va_arg(*args, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(*args, char *)));
	else if (c == 'p')
		return (ft_putptr(va_arg(*args, unsigned long)));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr_b(va_arg(*args, int), 10));
	else if (c == 'u')
		return (ft_putu(va_arg(*args, unsigned int)));
	else if (c == 'x')
		return (ft_putnbr_lu(va_arg(*args, unsigned int), 16, 'l'));
	else if (c == 'X')
		return (ft_putnbr_lu(va_arg(*args, unsigned int), 16, 'u'));
	else if (c == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		n_args;

	va_start(args, str);
	n_args = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1] != '\0')
		{
			n_args += ft_char_in_conditions(str[i + 1], &args);
			i++;
		}
		else
			n_args += ft_putchar(str[i]);
		i++;
	}
	va_end(args);
	return (n_args);
}
