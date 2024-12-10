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

	signal(SIGUSR1, &signal_handler);
	if (argc < 2) {
		ft_putendl_fd( "Missing server pid and message", STDOUT_FILENO);
		return 0;
	}
	if (argc < 3) {
		ft_putendl_fd( "Missing message", STDOUT_FILENO);
		return 0;
	}

	char* str = argv[1];
	if (!(ft_isdigit(*str) || *str == '-' || *str == '+')) {
			ft_putendl_fd( "Not a process id", STDOUT_FILENO);
			return 0;
	}
	str++;
	while (*str) {
		if (!ft_isdigit(*str)) {
			ft_putendl_fd( "Not a process id", STDOUT_FILENO);
			return 0;
		}
		str++;
	}

	server_pid = ft_atoi(argv[1]);

	if (server_pid <= 0) {
		ft_putendl_fd( "Server pid must be greater 0", STDOUT_FILENO);
		return 0;
	}
	if (kill(server_pid, 0) == -1) {
		if (errno == EPERM)
			ft_putendl_fd("You don't have permission to send a message to that target", STDOUT_FILENO);
		if (errno == ESRCH)
			ft_putendl_fd("The target you specified does not exist", STDOUT_FILENO);
		return (0);
	}
	send_msg(argv[2], server_pid);
	return (0);
}
