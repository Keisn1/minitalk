/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:19/55 by kfreyer           #+#    #+#             */
/*   Updated: 2024/07/31 15:19:55 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
   Appends src to string dst of size siz (unlike strncat, siz is the
   full size of dst, not space left).  At most siz-1 characters
   will be copied.  Always NUL terminates (unless siz <= strlen(dst)).
   Returns strlen(src) + MIN(siz, strlen(initial dst)).
   If retval >= siz, truncation occurred.
*/

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char		*d;
	const char	*s;
	size_t		dlen;
	size_t		n;

	n = size;
	d = dst;
	while (*d && n-- != 0)
		d++;
	dlen = d - dst;
	n = size - dlen;
	if (n == 0)
		return (ft_strlen(src) + dlen);
	s = src;
	while (*s)
	{
		if (n != 1)
		{
			*d++ = *s;
			n--;
		}
		s++;
	}
	*d = '\0';
	return (dlen + (s - src));
}
