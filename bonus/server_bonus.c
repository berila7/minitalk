/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:46:09 by mberila           #+#    #+#             */
/*   Updated: 2025/02/24 13:09:19 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk_bonus.h"

static t_data	g_data;

static void	handle_signal(int signum, siginfo_t *info, void *context)
{
	(void)context;
	
	// Store the client PID for acknowledgment
	g_data.client_pid = info->si_pid;
	
	if (signum == SIGUSR1)
		g_data.c |= (1 << g_data.bits);
	
	g_data.bits++;
	if (g_data.bits == 32)
	{
		ft_putchar_fd(g_data.c, 1);
		// Add newline if we receive null character for readability
		if (g_data.c == '\0')
			ft_putchar_fd('\n', 1);
		
		// Send acknowledgment to the client
		if (kill(g_data.client_pid, SIGUSR1) == -1)
			ft_printf("Error: Failed to send acknowledgment\n");
		
		g_data.c = 0;
		g_data.bits = 0;
	}
}

static void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_printf("Error setting up signal handler\n");
		exit(1);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_printf("Error setting up signal handler\n");
		exit(1);
	}
}

int	main(void)
{
	g_data.c = 0;
	g_data.bits = 0;
	g_data.client_pid = 0;
	
	ft_printf("Server PID: %d\n", getpid());
	ft_printf("Server ready to receive messages...\n");
	setup_signals();
	while (1)
		pause();
	return (0);
}
