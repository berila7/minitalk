/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:45:41 by mberila           #+#    #+#             */
/*   Updated: 2025/02/22 16:03:47 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

// Global variables to store received bits and bit position
static unsigned char received_char = 0;
static int bit_position = 0;

void handle_signal(int signum)
{
    if (signum == SIGUSR1)
        received_char |= (1 << bit_position);

    bit_position++;

    if (bit_position == 8)
    {
        write(1, &received_char, 1);
        received_char = 0;
        bit_position = 0;
    }
}

int main(void)
{
	printf("Process ID: %d\n", getpid());

	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	while(1)
		pause();
	return (0);
}