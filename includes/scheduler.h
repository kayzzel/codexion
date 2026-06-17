/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 11:21:21 by gabach            #+#    #+#             */
/*   Updated: 2026/06/17 12:55:30 by gabach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCHEDULER_H
# define SCHEDULER_H

// INCLUDES

# include "coders.h"
# include "codexion.h"

// FUNCS

int		scheduler(t_coder *coder, t_dongle *dongle);
int		get_dongle(t_coder *coder, t_dongle *dongle, t_app *app);
void	fifo(t_coder *coder, t_coder *heap_queue[2]);
void	edf(t_coder *coder, t_coder *heap_queue[2]);

#endif
