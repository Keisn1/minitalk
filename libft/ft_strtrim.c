/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 19:11/22 by kfreyer           #+#    #+#             */
/*   Updated: 2024/07/31 19:11:22 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	ft_chr_in_set(char const *set, char c)
{
	while (*set)
	{
		if (*set++ == c)
			return (1);
	}
	return (0);
}

const char	*find_start(char const *s1, char const *set)
{
	while (ft_chr_in_set(set, *s1))
		s1++;
	return (s1);
}

const char	*find_end(char const *s1, char const *set)
{
	while (ft_chr_in_set(set, *s1))
		s1--;
	return (s1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char const	*start;
	char const	*end;
	char		*res_o;
	char		*res;
	size_t		len_s1;

	len_s1 = ft_strlen(s1);
	if (!len_s1)
		return (ft_get_empty_str(1));
	start = find_start(s1, set);
	if (!*start)
		return (ft_get_empty_str(1));
	end = find_end(s1 + (len_s1 - 1), set);
	end++;
	res_o = (char *)malloc((end - start + 1) * sizeof(char));
	if (!res_o)
		return (NULL);
	res = res_o;
	while (start != end)
		*res++ = *start++;
	*res = '\0';
	return (res_o);
}
