/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 09:21/03 by kfreyer           #+#    #+#             */
/*   Updated: 2024/11/03 09:21:03 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "libft.h"

int	main(void)
{
	struct sigaction sa_msg;
	sa_msg.sa_sigaction = &string_handler;
	sa_msg.sa_flags = SA_SIGINFO;
	sigemptyset(&sa_msg.sa_mask);
	sigaction(SIGUSR1, &sa_msg, NULL);
	sigaction(SIGUSR2, &sa_msg, NULL);

	struct sigaction sa_shutdown;
	sa_shutdown.sa_handler = &interrupt_handler;
	sa_shutdown.sa_flags = 0;
	sigemptyset(&sa_shutdown.sa_mask);
	sigaction(SIGTERM, &sa_shutdown, NULL);
	sigaction(SIGINT, &sa_shutdown, NULL);

	ft_putstr_fd((char *)"Server pid: ", STDOUT_FILENO);
	ft_putnbr_fd(getpid(), STDOUT_FILENO);
	ft_putendl_fd((char *)"", STDOUT_FILENO);
	ft_putendl_fd((char *)"Ready to receive messages...", STDOUT_FILENO);
	while (1)
	{
		pause();
	}
	return (0);
}
