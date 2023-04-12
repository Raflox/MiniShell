/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 22:54:08 by rgomes-c          #+#    #+#             */
/*   Updated: 2022/10/28 19:09:03 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *s)
{
	int		i;
	int		x;

	x = 0;
	i = 0;
	if (!s)
		return (ft_putstr("(null)"));
	while (s[i])
	{
		x += ft_putchar(s[i]);
		i++;
	}
	return (x);
}
