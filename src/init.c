/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <gabach@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 16:48:35 by gabach            #+#    #+#             */
/*   Updated: 2026/05/27 18:41:36 by gabach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"
#include "exit.h"

#include <stdlib.h>
#include <string.h>

t_dongle	**init_dongles(int nb_coders, char scheduler[5])
{
	t_dongle	**dongles;
	int			index;
	int		(*func)(t_coder[2]);

	dongles = malloc(sizeof(t_dongle *) * (nb_coders - 1));
	if (dongles == NULL)
		return (NULL);
	func = NULL; // replace by edf function
	if (strcmp(scheduler, "fifo"))
		func = NULL; // replace by fifo func
	index = 0;
	while (index < nb_coders)
	{
		dongles[index] = malloc(sizeof(t_dongle));
		if (dongles[index] == NULL)
			return ((t_dongle**)free_dongles(dongles));
		dongles[index]->scheduler = func;
		dongles[index]->heap_queue[0] = NULL;
		dongles[index]->heap_queue[1] = NULL;
		index++;
	}
	dongles[index] = NULL;
	return (dongles);
}
