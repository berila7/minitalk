/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:46:13 by mberila           #+#    #+#             */
/*   Updated: 2025/02/24 13:15:16 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk_bonus.h"

static int	g_received = 0;

static void	handle_acknowledgment(int signum)
{
	(void)signum;
	g_received = 1;
	ft_printf("Message received by server!\n");
}

static void	send_char(int pid, int c)
{
	int	bit;
	int	timeout_counter;

	bit = 0;
	while (bit < 32)
	{
		g_received = 0;
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
		bit++;
		// Wait a bit for server response with timeout
		timeout_counter = 0;
		while (!g_received && timeout_counter < 50)
		{
			usleep(100);
			timeout_counter++;
		}
		// If no response after timeout, print warning but continue
		if (!g_received && bit == 32)
			ft_printf("Warning: No acknowledgment from server for this character\n");
	}
}

static void	send_message(int pid, char *message)
{
	ft_printf("Sending message to server...\n");
	while (*message)
	{
		send_char(pid, *message);
		message++;
	}
	// Send null terminator to properly end the message
	send_char(pid, '\0');
	ft_printf("Message transmission completed.\n");
}

int	main(int ac, char **av)
{
	struct sigaction	sa;

	if (ac != 3)
	{
		ft_printf("Usage: %s <server_pid> <message>\n", av[0]);
		return (1);
	}
	sa.sa_handler = handle_acknowledgment;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		return (1);
	if (ft_atoi(av[1]) <= 0)
	{
		ft_printf("Error: Invalid PID\n");
		return (1);
	}
	send_message(ft_atoi(av[1]), av[2]);
	return (0);
}