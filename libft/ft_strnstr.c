/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:51/04 by kfreyer           #+#    #+#             */
/*   Updated: 2024/07/31 11:51:04 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	n;

	if (!big && little && len == 0)
		return (NULL);
	if (ft_strlen(little) == 0)
		return ((char *)big);
	n = ft_strlen(little);
	if (!*little)
		return ((char *)big);
	while (*big && n <= len)
	{
		if (*big == *little && ft_strncmp(big, little, n) == 0)
			return ((char *)big);
		big++;
		len--;
	}
	return (NULL);
}
