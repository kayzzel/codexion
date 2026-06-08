/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kayzzel <gabach@student.42lyon.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 12:33:47 by kayzzel           #+#    #+#             */
/*   Updated: 2026/06/08 11:48:17 by gabach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

// INCLUDES

# include <pthread.h>

// FUNCS

int		is_positive_int(char *str);
void	mutex_print(pthread_mutex_t *mutex, char *str, int coder_id);

#endif
