/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_num_of_digits_unsigned.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:25/25 by kfreyer           #+#    #+#             */
/*   Updated: 2024/09/03 16:25:25 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_num_of_digits_unsigned(unsigned int d)
{
	int	count;

	count = 1;
	while (d >= 10)
	{
		d /= 10;
		count++;
	}
	return (count);
}
