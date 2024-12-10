/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:58/03 by kfreyer           #+#    #+#             */
/*   Updated: 2024/12/10 21:58:03 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stdbool.h>
# include <unistd.h>

extern volatile sig_atomic_t	g_server_signal_received;

int								validate_pid_str(char *pid);
int								argument_validation(int argc, char *argv[]);
int								server_pid_validation(int server_pid);
void							client_signal_handler(int signal);
void							string_handler(int sig, siginfo_t *siginfo,
									void *ucontext);
void							interrupt_handler(int signal);
void							send_char(char c, pid_t pid);
void							send_msg(char *msg, pid_t server_pid);

#endif // MINITALK_H
