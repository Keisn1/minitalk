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

#include "minitalk.h"
#include <signal.h>
#include <unistd.h>
#include "libft.h"

void	signal_handler(int signal)
{
	static unsigned			signals_received = 0;
	static unsigned char	c = 0;

#ifdef UNIT_TEST /* PreprocessorDirective */
	if (signal == -1)
	{
		signals_received = 0;
		return ;
	}
#endif

	signals_received++;
	c = c >> 1;
	if (signal == SIGUSR1)
		c = c | 0b10000000;
	if (signals_received == 8)
		ft_putchar_fd(c, STDOUT_FILENO);
}
