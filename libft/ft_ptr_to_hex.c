/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptr_to_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:30/21 by kfreyer           #+#    #+#             */
/*   Updated: 2024/09/03 15:30:21 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ptr_to_hex(void *p, char *hex_str)
{
	const char	*hex_chars = "0123456789abcdef";
	int			pos;
	int			digits;
	char		c;

	digits = 1;
	pos = 15;
	while (pos >= 0)
	{
		c = hex_chars[((long unsigned)p >> (pos * 4)) & 0xF];
		if (c != '0' && digits == 1)
			digits = pos + 1;
		hex_str[15 - pos] = c;
		pos--;
	}
	hex_str[16] = '\0';
	return (digits);
}
