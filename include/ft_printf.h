/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:06:22 by rgomes-c          #+#    #+#             */
/*   Updated: 2022/10/28 23:10:41 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>

int		ft_printf(const char *str, ...);
int		ft_putnbr_b(long n, int base);
int		ft_putnbr_lu(unsigned int n, unsigned int b, char x);
int		ft_putptr(unsigned long nb);
int		ft_putu(unsigned int n);
int		ft_putchar(char c);
int		ft_putstr(char *s);

#endif