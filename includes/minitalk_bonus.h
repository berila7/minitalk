/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:08:48 by mberila           #+#    #+#             */
/*   Updated: 2025/02/21 12:08:58 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

#include <unistd.h>
#include <signal.h>
#include "../libft/libft.h"
#include "../ft_printf/ft_printf.h"

typedef struct s_data
{
	unsigned char	received_char;
	int				bit_position;
}	t_data;

#endif