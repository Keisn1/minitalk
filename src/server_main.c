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
#include <signal.h>
#include <stdbool.h>
#include <unistd.h>

int	main(void)
{
	struct sigaction action;
	action.sa_sigaction = &string_handler;
	action.sa_flags = SA_SIGINFO;
	sigemptyset(&action.sa_mask);
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);

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
