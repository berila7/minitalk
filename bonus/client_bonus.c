/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:46:13 by mberila           #+#    #+#             */
/*   Updated: 2025/02/21 16:46:14 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk_bonus.h"

void	send_char(int pid, char c)
{
	int bit;

	bit = 0;
	while (bit < 8)
	{
		if (c & (1 << bit))
		{
			if (kill(pid, SIGUSR1) == -1)
				exit(1);
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				exit(1);
		}
		usleep(50);
		bit++;
	}
}

static void	send_message(int pid, char *message)
{
	int i;

	i = 0;
	while (message[i])
	{
		send_char(pid, message[i]);
		i++;
	}
}

#include "../includes/minitalk.h"

int	main(int ac, char *av[])
{
	char *message;
	int pid;

	if (ac != 3)
	{
		 ft_printf("Usage: %s <server_pid> <message>\n", av[0]);
		return (1);
	}
	message = av[2];
	pid = ft_atoi(av[1]);
	if (pid <= 0)
	{
		ft_printf("Error: Invalid PID\n");
		return (1);
	}
	send_message(pid, message);
	return (0);
}
