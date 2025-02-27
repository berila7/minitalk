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

static void	handle_signal(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;

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
	struct sigaction	sa;

	g_data.received_char = 0;
	g_data.bit_position = 0;

	// Set up signal handlers using sigaction (compliant with allowed functions)
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_printf("Error setting up signal handler\n");
		return (1);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_printf("Error setting up signal handler\n");
		return (1);
	}

	ft_printf("Server PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}