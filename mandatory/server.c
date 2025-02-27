/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:45:41 by mberila           #+#    #+#             */
/*   Updated: 2025/02/24 13:54:00 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

// Global variables to store received bits and bit position
static t_data	g_data;

// Handle timeouts for interrupted transmissions
static void	handle_timeout(int signum)
{
	(void)signum;
	if (g_data.bit_position > 0)
	{
		ft_printf("\n[Reset] Incomplete transmission detected\n");
		g_data.received_char = 0;
		g_data.bit_position = 0;
	}
}

void	handle_signal(int signum)
{
	// Reset the timeout alarm each time we receive a bit
	alarm(1);

	if (signum == SIGUSR1)
		g_data.received_char |= (1 << g_data.bit_position);

	g_data.bit_position++;
	if (g_data.bit_position == 8)
	{
		ft_putchar_fd(g_data.received_char, 1);
		g_data.received_char = 0;
		g_data.bit_position = 0;
	}
}

int	main(void)
{
	g_data.received_char = 0;
	g_data.bit_position = 0;

	// Set up signal handlers
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	signal(SIGALRM, handle_timeout);

	ft_printf("Server PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}