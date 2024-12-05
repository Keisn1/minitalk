/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 08:33/50 by kfreyer           #+#    #+#             */
/*   Updated: 2024/11/03 08:33:50 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minitalk.h"
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t	server_signal_received = 0;

void	signal_handler(int signal)
{
	(void)signal;
	server_signal_received = 1;
}

void	send_char(char c, pid_t pid)
{
	int				count;
	unsigned char	bit;

	count = 0;
	while (count < 8)
	{
		bit = (c >> count) & 1;
		if (bit)
		{
			kill(pid, SIGUSR1);
			while (server_signal_received == 0)
			{
				pause();
			}
			server_signal_received = 0;
		}
		else
		{
			kill(pid, SIGUSR2);
			while (server_signal_received == 0)
			{
				pause();
			}
			server_signal_received = 0;
		}
		count++;
	}
}

