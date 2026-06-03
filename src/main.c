/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <gabach@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 10:27:26 by gabach            #+#    #+#             */
/*   Updated: 2026/06/03 11:27:52 by gabach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "init.h"
#include "exit.h"

#include <string.h>

int	main(int argc, char **argv)
{
	t_app	*app;

	app = init_codexion(argc, argv);
	if (app == NULL)
		return (1);
	free_app(app);
}
