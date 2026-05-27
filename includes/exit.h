/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <gabach@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 17:06:49 by gabach            #+#    #+#             */
/*   Updated: 2026/05/27 17:38:39 by gabach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H

// INCLUDES

# include "coders.h"

// FUNCS

char	*free_dongles(t_dongle **dongles);
char	*free_coders(t_coder **coders);

#endif
