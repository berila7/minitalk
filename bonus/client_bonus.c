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

static int	is_valid_pid(char *str)
{
	int	i;
	int	pid;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	if (i == 0)
		return (0);
	pid = ft_atoi(str);
	if (pid <= 0 || pid > 99999)
		return (0);
	return (1);
}

static void	handle_acknowledgment(int signum)
{
	(void)signum;
	g_received = 1;
}

static void	send_signal(int pid, int bit_value)
{
	if (bit_value)
	{
		if (kill(pid, SIGUSR1) == -1)
		{
			ft_printf("Error: Failed to send signal\n");
			exit(1);
		}
	}
	else
	{
		if (kill(pid, SIGUSR2) == -1)
		{
			ft_printf("Error: Failed to send signal\n");
			exit(1);
		}
	}
}

static void	send_char(int pid, int c)
{
	int	bit;

	bit = 0;
	while (bit < 32)
	{
		g_received = 0;
		send_signal(pid, c & (1 << bit));
		usleep(100);
		bit++;
	}
	usleep(500);
	if (!g_received)
		ft_printf("Warning: No acknowledgment received from server\n");
}

static void	send_message(int pid, char *message)
{
	ft_printf("Sending message to server...\n");
	while (*message)
	{
		send_char(pid, *message);
		message++;
	}
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
	if (!is_valid_pid(av[1]))
	{
		ft_printf("Error: Invalid PID format. PID must be a positive number.\n");
		return (1);
	}
	sa.sa_handler = handle_acknowledgment;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_printf("Error setting up signal handler\n");
		return (1);
	}
	send_message(ft_atoi(av[1]), av[2]);
	return (0);
}