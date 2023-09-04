/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 21:08:02 by rafilipe          #+#    #+#             */
/*   Updated: 2022/10/27 16:25:18 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t number, size_t size)
{
	void	*ptr;

	if (number > SIZE_MAX / size)
		return (NULL);
	ptr = malloc(number * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, size * number);
	return (ptr);
}
