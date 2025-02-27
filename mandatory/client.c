/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:46:32 by mberila           #+#    #+#             */
/*   Updated: 2025/02/23 09:33:58 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

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

void	send_char(int pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if (c & (1 << bit))
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
		usleep(100);
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
		i++;
	}
	send_char(pid, '\n');
}

int	main(int ac, char *av[])
{
	char	*message;
	int		pid;

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
	message = av[2];
	pid = ft_atoi(av[1]);
	send_message(pid, message);
	return (0);
}
