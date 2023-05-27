/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:11:45 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/04/24 13:53:39 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int	put_str(char *s)
{
	int		i;
	int		x;

	x = 0;
	i = 0;
	if (!s)
		return (put_str("(null)"));
	while (s[i])
	{
		x += write(1, &s[i], 1);
		i++;
	}
	return (x);
}

static int	put_n(long long int num, int base, int up_c)
{
	char	*b1;
	char	*b2;
	int		x;

	b1 = "0123456789abcdef";
	b2 = "0123456789ABCDEF";
	x = 0;
	if (num < 0)
	{
		write(1, "-", 1);
		x += put_n(-num, base, up_c) + 1;
	}
	else if (num < base)
	{
		if (up_c == 0)
			x += write(1, &b1[num], 1);
		else
			x += write(1, &b2[num], 1);
	}
	else
		x += put_n(num / base, base, up_c) + put_n(num % base, base, up_c);
	return (x);
}

static int	ptr(unsigned long long num, int flag)
{
	int		x;
	char	*s;

	s = "0123456789abcdef";
	if (!num && flag == 1)
		return (put_str("(nil)"));
	x = 0;
	if (flag == 1)
		x += put_str("0x");
	if (num < 16)
		x += write(1, &s[num], 1);
	else
		x += ptr(num / 16, 0) + ptr(num % 16, 0);
	return (x);
}

static int	ft_char_in_conditions(char c, va_list *args)
{
	char	character;

	if (c == 'c')
	{
		character = va_arg(*args, int);
		return (write(1, &character, 1));
	}
	else if (c == 's')
		return (put_str(va_arg(*args, char *)));
	else if (c == 'p')
		return (ptr((unsigned long)va_arg(*args, unsigned long), 1));
	else if (c == 'd' || c == 'i')
		return (put_n(va_arg(*args, int), 10, 0));
	else if (c == 'u')
		return (put_n((unsigned int)va_arg(*args, unsigned int), 10, 0));
	else if (c == 'x')
		return (put_n((unsigned int)va_arg(*args, unsigned int), 16, 0));
	else if (c == 'X')
		return (put_n((unsigned int)va_arg(*args, unsigned int), 16, 1));
	else if (c == '%')
		return (write(1, "%", 1));
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
			n_args += write(1, &str[i], 1);
		i++;
	}
	va_end(args);
	return (n_args);
}
