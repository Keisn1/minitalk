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

volatile sig_atomic_t	g_server_signal_received = 0;

void	client_signal_handler(int signal)
{
	if (signal == SIGUSR1)
		g_server_signal_received = 1;
	if (signal == SIGUSR2)
		ft_putendl_fd("Server: \"Message received\"", STDOUT_FILENO);
	return ;
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
			while (g_server_signal_received == 0)
				pause();
		}
		else
		{
			kill(pid, SIGUSR2);
			while (g_server_signal_received == 0)
				pause();
		}
		g_server_signal_received = 0;
		count++;
	}
}

void	send_msg(char *msg, pid_t server_pid)
{
	while (*msg)
	{
		send_char(*msg, server_pid);
		msg++;
	}
	send_char(*msg, server_pid);
}
