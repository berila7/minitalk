/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:46:09 by mberila           #+#    #+#             */
/*   Updated: 2025/02/21 17:19:49 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk_bonus.h"

static t_data	g_data;

static void	handle_signal(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (signum == SIGUSR1)
		g_data.c |= (1 << g_data.bits);
	g_data.bits++;
	if (g_data.bits == 8)
	{
		ft_putchar_fd(g_data.c, 1);
		ft_printf(" [Received from PID: %d]\n", info->si_pid);
		kill(info->si_pid, SIGUSR1);
		g_data.c = 0;
		g_data.bits = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	g_data.c = 0;
	g_data.bits = 0;
	ft_printf("\n=== Server Started ===\n");
	ft_printf("Server PID: %d\n", getpid());
	ft_printf("Waiting for messages...\n\n");
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}