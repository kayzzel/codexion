/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <gabach@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 17:06:49 by gabach            #+#    #+#             */
/*   Updated: 2026/06/18 13:15:17 by gabach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H

// INCLUDES

# include "coders.h"
# include "codexion.h"

// FUNCS

char	*free_dongles(t_dongle **dongles);
char	*free_coders(t_coder **coders);
t_app	*free_app(t_app *app);
int		test_mutex_cond_init(t_app *app, int cond_init, int mutex_init);
void	exit_threads(t_app *app, int nb_created, pthread_t *coders_threads);

#endif
