/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:17:24 by rafilipe          #+#    #+#             */
/*   Updated: 2022/10/14 15:38:11 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nbrcount(int a)
{
	size_t	len;

	len = 0;
	if (a == 0)
		len++;
	if (a < 0)
	{
		a *= -1;
		len++;
	}
	while (a)
	{
		a /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int a)
{
	char		*str;
	size_t		len;
	long int	nb;

	nb = a;
	len = ft_nbrcount(nb);
	str = (char *)malloc(len * sizeof(char) + 1);
	if (!str)
		return (NULL);
	if (a == 0)
		str[0] = 48;
	str[len--] = '\0';
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	while (nb > 0)
	{
		str[len--] = 48 + nb % 10;
		nb /= 10;
	}
	return (str);
}
