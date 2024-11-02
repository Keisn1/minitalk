/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:55/48 by kfreyer           #+#    #+#             */
/*   Updated: 2024/07/31 17:55:48 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	len_s;
	size_t	count;
	char	*new;

	len_s = ft_strlen(s);
	if (start >= len_s)
		return (ft_get_empty_str(1));
	if ((len_s - start) < len)
		len = len_s - start;
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	count = 0;
	while (count < len)
	{
		new[count++] = s[start];
		start++;
	}
	new[count] = '\0';
	return (new);
}
