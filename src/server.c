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
#include <signal.h>
#include <stdbool.h>
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

char	*update_buffer(size_t length, unsigned int signals_received, bool reset)
{
	static size_t	buffer_size = 0;
	static char		*buffer = NULL;

	if (reset)
	{
		free(buffer);
		buffer = NULL;
		buffer_size = 0;
	}
	if (buffer_size == 0)
	{
		buffer_size = 2;
		buffer = (char *)malloc(sizeof(char) * buffer_size);
		ft_bzero(buffer, sizeof(char) * 2);
	}
	if ((buffer_size == length) && (signals_received % 8 == 0))
	{
		buffer_size *= 2;
		buffer = (char *)ft_realloc(buffer, sizeof(char) * buffer_size,
				sizeof(char) * length);
	}
	return (buffer);
}

void	string_handler(int signal)
{
	char				*buffer;
	static size_t		length = 0;
	static unsigned int	signals_received = 0;

	buffer = update_buffer(length, signals_received, false);
	if (signal == SIGUSR1)
		buffer[length] = (buffer[length] >> 1) | 0b10000000;
	else if (signal == SIGUSR2)
		buffer[length] = (buffer[length] >> 1) & 0b01111111;
	signals_received++;
	if (signals_received % 8 == 0)
	{
		if (buffer[length] == '\0')
		{
			ft_putendl_fd((char *)buffer, STDOUT_FILENO);
			update_buffer(0, 0, true);
			length = 0;
			signals_received = 0;
			return ;
		}
		length++;
	}
}

void	interrupt_handler(int signal)
{
	if (signal == SIGTERM || signal == SIGINT)
	{
		ft_putendl_fd((char *)"Goodbye.", STDOUT_FILENO);
		exit(0);
	}
}
