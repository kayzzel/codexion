/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kayzzel <gabach@student.42lyon.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 12:33:47 by kayzzel           #+#    #+#             */
/*   Updated: 2026/06/15 16:36:08 by gabach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

// INCLUDES

# include "codexion.h"

# include <pthread.h>

// FUNCS

int		is_positive_int(char *str);
void	mutex_print(pthread_mutex_t *mutex, char *str, int coder_id);
void	init_time(void);
int		get_time_usec(void);
int		msleep(int msec, t_app *app);

#endif
