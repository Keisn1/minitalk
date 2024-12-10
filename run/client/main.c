/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 09:29/42 by kfreyer           #+#    #+#             */
/*   Updated: 2024/11/03 09:29:42 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minitalk.h"
#include <unistd.h>

int	main(int argc, char *argv[])
{
	pid_t	server_pid;

	signal(SIGUSR1, &client_signal_handler);
	signal(SIGUSR2, &client_signal_handler);

	if (argument_validation(argc, argv))
		return (1);

	server_pid = ft_atoi(argv[1]);
	if (server_pid_validation(server_pid))
		return (1);

	send_msg(argv[2], server_pid);
	pause();
	return (0);
}
