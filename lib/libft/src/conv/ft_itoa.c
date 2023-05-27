/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 20:44:38 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/04/24 13:53:39 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int	ft_count_numbers(long int n)
{
	int		i;

	i = 0;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i + 1);
}

char	*ft_itoa(int n)
{
	char	*itoa;
	int		itoa_size;
	int		i;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	itoa_size = ft_count_numbers(n);
	itoa = malloc((ft_count_numbers(n) + 1) * sizeof(char));
	if (!itoa)
		return (0);
	itoa[itoa_size--] = '\0';
	i = 0;
	if (n < 0)
	{
		itoa[0] = '-';
		n = -n;
		i = 1;
	}
	while (itoa_size >= i)
	{
		itoa[itoa_size--] = n % 10 + 48;
		n /= 10;
	}
	return (itoa);
}
