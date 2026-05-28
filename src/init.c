/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <gabach@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 16:48:35 by gabach            #+#    #+#             */
/*   Updated: 2026/05/28 18:49:31 by gabach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"
#include "exit.h"
#include "parsing.h"

#include <pthread.h>
#include <stdlib.h>
#include <string.h>

t_dongle	*create_dongle(char scheduler[5])
{
	t_dongle	*dongle;
	int			(*func)(t_coder[2]);

	dongle = malloc(sizeof(t_dongle));
	if (dongle == NULL)
		return (NULL);
	func = NULL; // replace by edf function
	if (strcmp(scheduler, "fifo"))
		func = NULL; // replace by fifo func
	if (pthread_mutex_init(&dongle->mutex, NULL) != 0)
	{
		free(dongle);
		return (NULL);
	}
	if (pthread_cond_init(&dongle->cond, NULL))
	{
		free(dongle);
		pthread_mutex_destroy(&dongle->mutex);
		return (NULL);
	}
	dongle->scheduler = func;
	dongle->heap_queue[0] = NULL;
	dongle->heap_queue[1] = NULL;
	return (dongle);
}

t_coder	*create_coder(int coder, t_args args, t_dongles *left,t_dongle *right)
{
	coder
}

t_dongle	**init_dongles(int nb_coders, char scheduler[5])
{
	t_dongle	**dongles;
	int			index;

	dongles = malloc(sizeof(t_dongle *) * (nb_coders + 1));
	if (dongles == NULL)
		return (NULL);
	index = 0;
	while (index < nb_coders)
	{
		dongles[index] = create_dongle(scheduler);
		if (dongles[index] == NULL)
		{
			dongles[index] = NULL;
			free_dongles(dongles);
			return (NULL);
		}
		index++;
	}
	dongles[index] = NULL;
	return (dongles);
}

t_coder	**init_coders(int nb_coders, t_dongle **dongles, t_args args)
{
	t_coder	**coders;
	int		index;

	coders = malloc(sizeof(t_coder *) * (nb_coders + 1));
	if (coders == NULL)
		return (NULL);
	index = 0;
	while (index < nb_coders)
	{
		index++;
	}
	coders[index] = NULL;
	return (coders);
}
