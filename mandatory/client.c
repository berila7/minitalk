/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:46:32 by mberila           #+#    #+#             */
/*   Updated: 2025/02/22 16:10:03 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	send_char(int server_id, char c)
{
	int bit;

	bit = 9;
	while (bit--)
	{
		if (c & (1 << bit))
			kill(server_id, SIGUSR1);
		else
			kill(server_id, SIGUSR2);
		usleep(100);
	}
}

#include "../includes/minitalk.h"

int	main(int ac, char *av[])
{
	if (ac != 3)
	{
		 printf("Usage: %s <server_pid> <message>\n", av[0]);
		return (1);
	}
	char *message;
	int server_id;
	int i;

	message = av[2];
	server_id = ft_atoi(av[1]);
	i = 0;
	while (message[i])
	{
		send_char(server_id, message[i]);
		i++;
	}
	return (0);
}