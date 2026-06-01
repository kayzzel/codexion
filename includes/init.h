/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 14:09:25 by gabach            #+#    #+#             */
/*   Updated: 2026/06/01 14:18:52 by gabach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

// INCLUDES

# include "coders.h"
# include "parsing.h"

// FUNCS

t_coder		**init_coders(t_args *args, t_dongle **dongles);
t_dongle	**init_dongles(int nb_coders, char scheduler[5]);

#endif
