/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <kfreyer@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:47:26 by kfreyer           #+#    #+#             */
/*   Updated: 2024/07/31 14:40:22 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*res_o;
	char	*res;
	int		len;

	len = ft_strlen(s);
	res = malloc((len + 1) * sizeof(char));
	if (res == (void *)0)
	{
		return (res);
	}
	res_o = res;
	while (*s)
		*res++ = *s++;
	*res = '\0';
	return (res_o);
}
