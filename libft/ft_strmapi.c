/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:49/51 by kfreyer           #+#    #+#             */
/*   Updated: 2024/08/15 13:49:51 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new;
	size_t	idx;

	if (f == NULL)
		return (ft_strdup(s));
	new = malloc(ft_strlen(s) + 1 * sizeof(char));
	if (new == NULL)
		return (new);
	idx = 0;
	while (s[idx])
	{
		new[idx] = (*f)(idx, s[idx]);
		idx++;
	}
	new[idx] = '\0';
	return (new);
}
