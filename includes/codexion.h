/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kayzzel <gabach@student.42lyon.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 10:32:10 by kayzzel           #+#    #+#             */
/*   Updated: 2026/06/15 15:05:07 by gabach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

// INCLUDES

# include "coders.h"
# include "parsing.h"
# include <pthread.h>

// STRUCTS

typedef struct s_app
{
	int				init;
	int				end;
	t_args			*args;
	t_coder			**coders;
	t_dongle		**dongles;
	pthread_cond_t	start_cond;
	pthread_mutex_t	app_mutex;
	pthread_t		*coder_threads;
}				t_app;

typedef struct s_codet_pth_arg
{
	t_app	*app;
	t_coder	*coder;
}				t_coder_pth_arg;

#endif
