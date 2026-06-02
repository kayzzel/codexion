/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <gabach@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 10:27:26 by gabach            #+#    #+#             */
/*   Updated: 2026/06/02 15:40:39 by gabach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"
#include "parsing.h"
#include "init.h"
#include "exit.h"

#include <string.h>

int	main(int argc, char **argv)
{
	static t_args	args = {0};
	t_dongle		**dongles;
	t_coder			**coders;

	if (parsing(&args, argc - 1, argv + 1))
		return (1);
	dongles = init_dongles(args.nb_coders, args.scheduler);
	if (dongles == NULL)
		return (1);
	coders = init_coders(&args, dongles);
	if (coders == NULL)
		return (1);
	exit_free(coders, dongles);
	return (0);
}
