/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kayzzel <gabach@student.42lyon.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 10:32:10 by kayzzel           #+#    #+#             */
/*   Updated: 2026/06/08 12:42:30 by gabach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

// INCLUDES

# include "coders.h"
# include "parsing.h"
#include <bits/pthreadtypes.h>
# include <pthread.h>

// STRUCTS

typedef struct s_app
{
	int				*init;
	t_args			*args;
	t_coder			**coders;
	t_dongle		**dongles;
	pthread_cond_t	start_cond;
	pthread_mutex_t	print_mutex;
}				t_app;

#endif
