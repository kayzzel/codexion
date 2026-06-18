/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <gabach@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 10:27:26 by gabach            #+#    #+#             */
/*   Updated: 2026/06/18 16:21:10 by gabach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "init.h"
#include "exit.h"
#include "utils.h"

#include <string.h>

int	main(int argc, char **argv)
{
	t_app	*app;

	app = init_codexion(argc, argv);
	if (app == NULL)
		return (1);
	init_time();
	if (init_treads(app))
		return (1);
	free_app(app);
	return (0);
}
