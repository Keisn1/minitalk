/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_empty_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 20:11/36 by kfreyer           #+#    #+#             */
/*   Updated: 2024/09/05 20:11:36 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_get_empty_str(size_t n)
{
	char	*ret;

	ret = (char *)malloc(n);
	if (ret == NULL)
		return (NULL);
	*ret = '\0';
	return (ret);
}
