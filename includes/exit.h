/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <gabach@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 17:06:49 by gabach            #+#    #+#             */
/*   Updated: 2026/06/08 13:31:02 by gabach           ###   ########.fr       */
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
void	exit_threads(t_app *app, pthread_t *coders_threads);

#endif
