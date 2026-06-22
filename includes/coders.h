/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kayzzel <gabach@student.42lyon.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 18:42:44 by kayzzel           #+#    #+#             */
/*   Updated: 2026/06/22 09:28:13 by gabach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODERS_H
# define CODERS_H

// INCLUDES

# include <pthread.h>
# include "parsing.h"

// STRUCTS

typedef struct s_dongle	t_dongle;

typedef struct s_coder
{
	int				id;
	int				*init;
	t_dongle		*left_dongle;
	t_dongle		*right_dongle;
	t_args			*infos;
	int				last_compile;
	int				nb_compile;
	pthread_mutex_t	mutex;
}				t_coder;

typedef struct s_dongle
{
	t_coder			*heap_queue[2];
	void			(*heap_manager)(t_coder*, t_coder*[2], pthread_mutex_t*);
	int				last_compile;
	pthread_mutex_t	mutex;
	int				held;
}				t_dongle;

// FUNCS

void	*coder_thread_init(void	*coder_ptr);

#endif 
