/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 09:44/00 by kfreyer           #+#    #+#             */
/*   Updated: 2024/11/02 09:44:00 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minitalk.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void	*ft_realloc(void *ptr, size_t size, size_t cpy_size)
{
	void	*new_ptr;

	if (!ptr)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(size);
	if (!new_ptr)
		return (NULL);
	ft_bzero(new_ptr, size);
	new_ptr = ft_memcpy(new_ptr, ptr, cpy_size);
	free(ptr);
	return (new_ptr);
}

unsigned char	*get_buffer(size_t length, unsigned int signals_received,
		bool reset)
{
	static size_t			buffer_size = 0;
	static unsigned char	*buffer = NULL;

	if (reset)
	{
		free(buffer);
		buffer = NULL;
		buffer_size = 0;
	}
	if (buffer_size == 0)
	{
		buffer_size = 2;
		buffer = (unsigned char *)malloc(sizeof(unsigned char) * buffer_size);
		ft_bzero(buffer, sizeof(unsigned char) * 2);
	}
	if ((buffer_size == length) && (signals_received % 8 == 0))
	{
		buffer_size *= 2;
		buffer = (unsigned char *)ft_realloc(buffer, sizeof(unsigned char)
				* buffer_size, sizeof(unsigned char) * length);
	}
	return (buffer);
}

void	signal_handler(int signal)
{
	bool				nullbyte;
	unsigned char		*buffer;
	static size_t		length = 0;
	static unsigned int	signals_received = 0;

#ifdef UNIT_TEST
	if (signal == -1)
	{
		signals_received = 0;
		length = 0;
		buffer = NULL;
		return ;
	}
#endif
	buffer = get_buffer(length, signals_received, false);
	buffer[length] = buffer[length] >> 1;
	if (signal == SIGUSR1)
		buffer[length] = buffer[length] | 0b10000000;
	nullbyte = false;
	signals_received++;
	if (signals_received % 8 == 0)
	{
		ft_putchar_fd(buffer[length], STDOUT_FILENO);
		length++;
		if (buffer[length - 1] == '\0')
			nullbyte = true;
	}
	if (nullbyte)
	{
		ft_putstr_fd((char *)buffer, STDOUT_FILENO);
		get_buffer(0, 0, true);
	}
}
