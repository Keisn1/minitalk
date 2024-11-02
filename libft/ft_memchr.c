/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:11/04 by kfreyer           #+#    #+#             */
/*   Updated: 2024/07/31 13:11:04 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			idx;
	unsigned char	*ptr;
	unsigned char	cmp;

	ptr = (unsigned char *)s;
	cmp = (unsigned char)c;
	idx = 0;
	while (idx < n)
	{
		if (ptr[idx] == cmp)
			return ((void *)(ptr + idx));
		idx++;
	}
	return (NULL);
}
