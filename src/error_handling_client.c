/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_client.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:46/16 by kfreyer           #+#    #+#             */
/*   Updated: 2024/12/10 21:46:16 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minitalk.h"
#include <errno.h>


int	validate_pid_str(char *pid)
{
	if (!(ft_isdigit(*pid) || *pid == '-' || *pid == '+'))
	{
		ft_putendl_fd("Not a process id", STDOUT_FILENO);
		return (1);
	}
	pid++;
	while (*pid)
	{
		if (!ft_isdigit(*pid))
		{
			ft_putendl_fd("Not a process id", STDOUT_FILENO);
			return (1);
		}
		pid++;
	}
	return (0);
}

int	argument_validation(int argc, char *argv[])
{
	if (argc < 2)
	{
		ft_putendl_fd("Missing server pid and message", STDOUT_FILENO);
		return (1);
	}
	else if (argc < 3)
	{
		ft_putendl_fd("Missing message", STDOUT_FILENO);
		return (1);
	}
	return (validate_pid_str(argv[1]));
}

int	server_pid_validation(int server_pid)
{
	if (server_pid <= 0)
	{
		ft_putendl_fd("Server pid must be greater 0", STDOUT_FILENO);
		return (1);
	}
	if (kill(server_pid, 0) == -1)
	{
		if (errno == EPERM)
			ft_putendl_fd("You don't have permission to"
				" send a message to that target",
				STDOUT_FILENO);
		if (errno == ESRCH)
			ft_putendl_fd("The target you specified does not exist",
				STDOUT_FILENO);
		return (1);
	}
	return (0);
}
