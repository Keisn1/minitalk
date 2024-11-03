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

#include <signal.h>
#include <unistd.h>

void send_char(char c, pid_t pid) {
	int count = 0;
	while (count < 8) {
		unsigned char bit = (c >> count) & 1;
		if (bit) {
			kill(pid, SIGUSR1);
		} else {
			kill(pid, SIGUSR2);
		}
		usleep(200);
		count++;
	}
}

