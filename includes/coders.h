/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kayzzel <gabach@student.42lyon.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 18:42:44 by kayzzel           #+#    #+#             */
/*   Updated: 2026/05/27 17:23:34 by gabach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODERS_H
# define CODERS_H

// STRUCTS

typedef struct s_dongle	t_dongle;

typedef struct s_coder
{
	int			id;
	t_dongle	*left_dongle;
	t_dongle	*right_dongle;
	int			last_compile;
	int			time_to_compile;
	int			time_to_debug;
	int			time_to_refactor;
}				t_coder;

typedef struct s_dongle
{
	t_coder	*heap_queue[2];
	int		(*scheduler)(t_coder[2]);
}				t_dongle;

#endif 
