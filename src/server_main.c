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
	signal(SIGUSR1, string_handler);
	signal(SIGUSR2, string_handler);
	signal(SIGINT, interrupt_handler);
	signal(SIGTERM, interrupt_handler);
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
