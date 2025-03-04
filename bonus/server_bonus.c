/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:46:09 by mberila           #+#    #+#             */
/*   Updated: 2025/03/04 15:04:45 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk_bonus.h"

static t_data	g_data;

static void	handle_signal(int signum, siginfo_t *info, void *context)
{
	(void)context;
	
	if (g_data.pid == 0)
		g_data.pid = info->si_pid;
	if (info->si_pid != g_data.pid)
	{
		g_data.pid = 0;
		g_data.received_char = 0;
		g_data.bit_position = 0;
	}
	if (signum == SIGUSR1)
		g_data.received_char |= (1 << g_data.bit_position);
	g_data.bit_position++;
	if (g_data.bit_position == 32)
	{
		g_data.bit_position = 0;
		if (g_data.received_char == '\0')
		{
			ft_putchar_fd('\n', 1);
		}
		ft_putchar_fd(g_data.received_char, 1);
		kill(info->si_pid, SIGUSR1);
		g_data.received_char = 0;
	}
}

static void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
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
	ft_printf("Server PID: %d\n", getpid());
	setup_signals();
	while (1)
		pause();
	return (0);
}