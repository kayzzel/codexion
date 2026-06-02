/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kayzzel <gabach@student.42lyon.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 18:42:44 by kayzzel           #+#    #+#             */
/*   Updated: 2026/06/02 11:21:06 by gabach           ###   ########.fr       */
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
	int			id;
	t_dongle	*left_dongle;
	t_dongle	*right_dongle;
	t_args		*infos;
	int			last_compile;
	int			nb_compile;
}				t_coder;

typedef struct s_dongle
{
	t_coder			*heap_queue[2];
	int				(*scheduler)(t_coder[2]);
	int				last_compile;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
}				t_dongle;

#endif 
