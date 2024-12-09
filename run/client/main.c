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

int	main(int argc, char *argv[])
{
	pid_t	server_pid;

	(void)argc;
	signal(SIGUSR1, &signal_handler);
	server_pid = ft_atoi(argv[1]);
	send_msg(argv[2], server_pid);
	return (0);
}
