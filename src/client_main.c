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

int main(int argc, char *argv[]) {
	(void)argc;
	pid_t server_pid = ft_atoi(argv[1]);
	char* msg = argv[2];
	while (*msg) {
		send_char(*msg, server_pid);
		usleep(42);
		msg++;
	}
	send_char(*msg, server_pid);

    return 0;
}
