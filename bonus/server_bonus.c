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

// Global variables to store received bits and bit position
static t_data	g_data;

void handle_signal(int signum)
{
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

int main(void)
{
	g_data.received_char = 0;
	g_data.bit_position = 0;
	ft_printf("Process ID: %d\n", getpid());
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	while(1)
		pause();
	return (0);
}