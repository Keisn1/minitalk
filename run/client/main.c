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

#include "minitalk.h"
#include "libft.h"
#include <errno.h>

int	main(int argc, char *argv[])
{
	pid_t	server_pid;

	(void)argc;
	signal(SIGUSR1, &signal_handler);

	server_pid = ft_atoi(argv[1]);

	if (kill(server_pid, 0) == -1) {
		if (errno == EPERM) {
			ft_putendl_fd("You don't have permission to send a message to that target", STDOUT_FILENO);
		}
		if (errno == ESRCH) {
			ft_putendl_fd("The target you specified does not exist", STDOUT_FILENO);
		}
		return (0);
	}
	send_msg(argv[2], server_pid);
	return (0);
}
