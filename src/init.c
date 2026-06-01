/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <gabach@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 16:48:35 by gabach            #+#    #+#             */
/*   Updated: 2026/06/01 15:23:26 by gabach           ###   ########.fr       */
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
		pthread_mutex_destroy(&dongle->mutex);
		free(dongle);
		return (NULL);
	}
	dongle->scheduler = func;
	dongle->heap_queue[0] = NULL;
	dongle->heap_queue[1] = NULL;
	return (dongle);
}

t_coder	*create_coder(int id, t_args *args, t_dongle *left, t_dongle *right)
{
	t_coder	*coder;

	coder = malloc(sizeof(t_coder));
	if (coder == NULL)
		return (NULL);
	coder->id = id;
	coder->left_dongle = left;
	coder->right_dongle = right;
	coder->infos = args;
	return (coder);
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

t_coder	**init_coders(t_args *args, t_dongle **dongles)
{
	t_coder		**coders;
	int			index;
	int			nb_coders;

	nb_coders = args->nb_coders;
	coders = malloc(sizeof(t_coder *) * (nb_coders + 1));
	if (coders == NULL)
		return (NULL);
	index = 0;
	while (index < nb_coders)
	{
		coders[index] = create_coder(index, args, dongles[index],
				dongles[(index + nb_coders - 1) % nb_coders]);
		if (coders[index] == NULL)
		{
			coders[index] = NULL;
			free_coders(coders);
			free_dongles(dongles);
			return (NULL);
		}
		index++;
	}
	coders[index] = NULL;
	return (coders);
}
