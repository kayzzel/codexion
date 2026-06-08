/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 14:09:25 by gabach            #+#    #+#             */
/*   Updated: 2026/06/08 13:33:38 by gabach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

// INCLUDES

# include "codexion.h"

// FUNCS

t_app	*init_codexion(int argc, char **argv);
int		init_treads(t_app *app);

#endif
