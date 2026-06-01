/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kayzzel <gabach@student.42lyon.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 18:42:44 by kayzzel           #+#    #+#             */
/*   Updated: 2026/06/01 15:10:49 by gabach           ###   ########.fr       */
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
}				t_coder;

typedef struct s_dongle
{
	t_coder			*heap_queue[2];
	int				(*scheduler)(t_coder[2]);
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
}				t_dongle;

#endif 
