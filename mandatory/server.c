/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:45:41 by mberila           #+#    #+#             */
/*   Updated: 2025/02/22 15:44:40 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

// Global variables to store received bits and bit position
static unsigned char g_received_char = 0;
static int g_bit_position = 0;

void handle_signal(int signum)
{
    if (signum == SIGUSR1)
        g_received_char |= (1 << g_bit_position);

    g_bit_position++;

    if (g_bit_position == 8)
    {
        write(1, &g_received_char, 1);
        g_received_char = 0;
        g_bit_position = 0;
    }
}

int main(void)
{
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	printf("Process ID: %d\n", getpid());
	while(1)
		pause();
	return (0);
}