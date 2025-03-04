/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:08:48 by mberila           #+#    #+#             */
/*   Updated: 2025/03/04 15:02:52 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include <unistd.h>
# include <signal.h>
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"

typedef struct s_data
{
	unsigned int	received_char;
	int				bit_position;
	pid_t			pid;
}	t_data;

#endif