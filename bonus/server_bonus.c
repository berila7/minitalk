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

static void	handle_timeout(int signum)
{
	(void)signum;
	if (g_data.bits > 0)
	{
		ft_printf("\n[Warning] Incomplete transmission detected. Resetting...\n");
		g_data.c = 0;
		g_data.bits = 0;
		ft_printf("Server ready for new connections...\n");
	}
}

static void	handle_signal(int signum, siginfo_t *info, void *context)
{
	(void)context;
	
	// Reset timeout timer on each received signal
	alarm(1);
	
	if (signum == SIGUSR1)
		g_data.c |= (1 << g_data.bits);
	g_data.bits++;
	if (g_data.bits == 32)
	{
		ft_putchar_fd(g_data.c, 1);
		// Add newline if we receive null character for readability
		if (g_data.c == '\0')
			ft_putchar_fd('\n', 1);
		kill(info->si_pid, SIGUSR1);
		g_data.c = 0;
		g_data.bits = 0;
	}
}

static void	setup_signals(void)
{
	struct sigaction	sa;
	struct sigaction	sa_timeout;

	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		exit(1);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		exit(1);
	
	sa_timeout.sa_handler = handle_timeout;
	sa_timeout.sa_flags = 0;
	sigemptyset(&sa_timeout.sa_mask);
	if (sigaction(SIGALRM, &sa_timeout, NULL) == -1)
		exit(1);
}

int	main(void)
{
	g_data.c = 0;
	g_data.bits = 0;
	ft_printf("Server PID: %d\n", getpid());
	ft_printf("Server ready to receive messages...\n");
	setup_signals();
	while (1)
		pause();
	return (0);
}