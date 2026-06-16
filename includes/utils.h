/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kayzzel <gabach@student.42lyon.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 12:33:47 by kayzzel           #+#    #+#             */
/*   Updated: 2026/06/16 14:32:18 by gabach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

// INCLUDES

# include "codexion.h"

# include <pthread.h>

// FUNCS

int		program_ended(t_app *app);

int		is_positive_int(char *str);

int		init_mutex_print(pthread_mutex_t *mutex);
int		stop_mutex_print(void);
int		thread_print(char *str, int coder_id);
int		mutex_print(pthread_mutex_t *mutex, char *str, int coder_id);

void	init_time(void);
int		get_time_usec(void);
int		msleep(int msec, t_app *app);

#endif
