/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_unsigned_int_fd.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:26/44 by kfreyer           #+#    #+#             */
/*   Updated: 2024/09/03 16:26:44 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_put_unsigned_int_fd(unsigned int nb, int fd)
{
	int	arr[10];
	int	idx;

	idx = 0;
	arr[idx++] = ft_abs(nb % 10);
	nb = ft_abs(nb / 10);
	while (nb > 0)
	{
		arr[idx++] = nb % 10;
		nb /= 10;
	}
	while (--idx >= 0)
		ft_putchar_fd(arr[idx] + '0', fd);
}
