/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:46:09 by mberila           #+#    #+#             */
/*   Updated: 2025/03/07 11:39:31 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk_bonus.h"

static t_data	g_data;

static void	reset_state(void)
{
	g_data.pid = 0;
	g_data.received_char = 0;
	g_data.bit_position = 0;
	g_data.buffer_pos = 0;
	g_data.expected_bytes = 0;
	write(1, "\n", 1);
}

static int	get_utf8_bytes(unsigned char first_byte)
{
	if ((first_byte & 0x80) == 0)
		return (1);
	else if ((first_byte & 0xE0) == 0xC0)
		return (2);
	else if ((first_byte & 0xF0) == 0xE0)
		return (3);
	else if ((first_byte & 0xF8) == 0xF0)
		return (4);
	return (1);
}

static void	flush_character(void)
{
	int	i;

	if (g_data.buffer_pos == g_data.expected_bytes)
	{
		i = 0;
		while (i < g_data.buffer_pos)
		{
			write(1, &g_data.byte_buffer[i], 1);
			i++;
		}
	}
	g_data.buffer_pos = 0;
	g_data.expected_bytes = 0;
}

static void	handle_signal(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (g_data.pid == 0)
		g_data.pid = info->si_pid;
	if (info->si_pid != g_data.pid)
	{
		g_data.pid = info->si_pid;
		g_data.received_char = 0;
		g_data.bit_position = 0;
		g_data.buffer_pos = 0;
		g_data.expected_bytes = 0;
	}
	if (signum == SIGUSR1)
		g_data.received_char |= (1 << g_data.bit_position);
	g_data.bit_position++;
	if (g_data.bit_position == 8)
	{
		g_data.bit_position = 0;
		if (g_data.received_char == '\0')
		{
			flush_character();
			write(1, "\n", 1);
			reset_state();
			kill(info->si_pid, SIGUSR1);
			return ;
		}
		if (g_data.buffer_pos == 0)
			g_data.expected_bytes = get_utf8_bytes(g_data.received_char);
		g_data.byte_buffer[g_data.buffer_pos++] = g_data.received_char;
		if (g_data.buffer_pos >= g_data.expected_bytes)
			flush_character();
		kill(info->si_pid, SIGUSR1);
		g_data.received_char = 0;
	}
}

int	main(int ac, char **av)
{
	struct sigaction	sa;

	(void)av;
	if (ac != 1)
	{
		ft_printf("one argument allowed\n");
		return (1);
	}
	reset_state();
	ft_printf("Server PID: %d\n", getpid());
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_printf("Error setting up signal handler\n");
		exit(1);
	}
	while (1)
		pause();
	return (0);
}
