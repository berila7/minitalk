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

static int	g_received;

static void	signal_handler(int signum)
{
	(void)signum;
	g_received = 1;
	ft_printf("Character received by server!\n");
}

static void	send_char(int pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		g_received = 0;
		if (c & (1 << bit))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		bit++;
		while (!g_received)
			usleep(50);
	}
}

int	main(int ac, char **av)
{
	int		i;
	int		pid;

	if (ac != 3)
	{
		ft_printf("Usage: %s <server_pid> <message>\n", av[0]);
		return (1);
	}
	pid = ft_atoi(av[1]);
	if (pid <= 0)
	{
		ft_printf("Error: Invalid PID\n");
		return (1);
	}
	signal(SIGUSR1, signal_handler);
	i = 0;
	ft_printf("Sending message to server...\n");
	while (av[2][i])
		send_char(pid, av[2][i++]);
	ft_printf("\nComplete message sent successfully!\n");
	return (0);
}