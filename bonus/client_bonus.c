/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:46:13 by mberila           #+#    #+#             */
/*   Updated: 2025/03/07 14:26:40 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk_bonus.h"

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
	ft_printf("\033[0;32mMessage received by server!\n");
}

static void	send_char(int pid, int c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if (c & (1 << bit))
		{
			if (kill(pid, SIGUSR1) == -1)
			{
				ft_printf("\033[0;31mError: Failed to send signal\n");
				exit(1);
			}
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
			{
				ft_printf("\033[0;31mError: Failed to send signal\n");
				exit(1);
			}
		}
		usleep(255);
		bit++;
	}
}

static void	send_message(int pid, char *message)
{
	int	i;

	i = 0;
	while (message[i])
	{
		send_char(pid, message[i]);
		usleep(50);
		i++;
	}
	send_char(pid, '\0');
	usleep(100);
}

int	main(int ac, char **av)
{
	struct sigaction	sa;

	if (ac != 3)
	{
		ft_printf("\033[0;31mUsage: %s <server_pid> <message>\n", av[0]);
		return (1);
	}
	if (!is_valid_pid(av[1]))
	{
		ft_printf("\033[0;31mError: Invalid PID .\n");
		return (1);
	}
	sa.sa_handler = handle_acknowledgment;
	sa.sa_flags = 0;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		return (1);
	send_message(ft_atoi(av[1]), av[2]);
	return (0);
}
