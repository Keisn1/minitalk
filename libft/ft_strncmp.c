/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <kfreyer@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:06:13 by kfreyer           #+#    #+#             */
/*   Updated: 2024/07/31 10:38:52 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			count;
	unsigned int	idx;
	unsigned char	c1;
	unsigned char	c2;

	count = 0;
	idx = 0;
	while (s1[idx] != '\0' && s2[idx] != '\0' && count < n)
	{
		c1 = (unsigned char)s1[idx];
		c2 = (unsigned char)s2[idx];
		if (c1 != c2)
			return (c1 - c2);
		idx++;
		count++;
	}
	if (count == n)
		return (0);
	c1 = (unsigned char)s1[idx];
	c2 = (unsigned char)s2[idx];
	return (c1 - c2);
}
