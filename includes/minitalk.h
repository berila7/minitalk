/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:03:45 by mberila           #+#    #+#             */
/*   Updated: 2025/03/04 15:02:39 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"

typedef struct s_data
{
	unsigned char	received_char;
	int				bit_position;
	pid_t			pid;
}	t_data;

#endif