/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_app.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <gabach@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 16:48:35 by gabach            #+#    #+#             */
/*   Updated: 2026/06/15 17:19:02 by gabach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"
#include "exit.h"
#include "parsing.h"
#include "codexion.h"
#include "utils.h"

#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

static t_dongle	*create_dongle(char scheduler[5])
{
	t_dongle	*dongle;
	int			(*func)(t_coder[2]);

	dongle = malloc(sizeof(t_dongle));
	if (dongle == NULL)
		return (NULL);
	func = NULL; // replace by edf function
	if (strcmp(scheduler, "fifo") == 0)
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
	dongle->last_compile = 0;
	return (dongle);
}

static t_coder	*create_coder(
			int id,
			t_app *app
		)
{
	t_coder	*coder;
	int		nb_coders;

	coder = malloc(sizeof(t_coder));
	if (coder == NULL)
		return (NULL);
	if (pthread_mutex_init(&coder->mutex, NULL))
	{
		free(coder);
		return (NULL);
	}
	nb_coders = app->args->nb_coders;
	coder->id = id;
	coder->left_dongle = app->dongles[id];
	coder->right_dongle = app->dongles[id];
	if (id % 2 == 0)
		coder->right_dongle = app->dongles[(id + nb_coders - 1) % nb_coders];
	else
		coder->left_dongle = app->dongles[(id + nb_coders - 1) % nb_coders];
	coder->infos = app->args;
	coder->nb_compile = 0;
	coder->last_compile = 0;
	coder->init = &app->init;
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
			free_dongles(dongles);
			return (NULL);
		}
		index++;
	}
	dongles[index] = NULL;
	return (dongles);
}

t_coder	**init_coders(t_app *app)
{
	t_coder		**coders;
	int			index;

	if (app->dongles == NULL)
		return (NULL);
	coders = malloc(sizeof(t_coder *) * (app->args->nb_coders + 1));
	if (coders == NULL)
		return (NULL);
	index = 0;
	while (index < app->args->nb_coders)
	{
		coders[index] = create_coder(index + 1, app);
		if (coders[index] == NULL)
		{
			free_coders(coders);
			free_dongles(app->dongles);
			return (NULL);
		}
		index++;
	}
	coders[index] = NULL;
	return (coders);
}

t_app	*init_codexion(int argc, char **argv)
{
	t_app	*app;

	app = malloc(sizeof(t_app));
	if (app == NULL)
		return (NULL);
	app->init = 0;
	app->end = 0;
	app->args = NULL;
	if (pthread_cond_init(&app->start_cond, NULL) != 0
		|| pthread_mutex_init(&app->app_mutex, NULL) != 0)
		return (free_app(app));
	app->args = parsing(argc - 1, argv + 1);
	if (app->args == NULL)
	{
		pthread_cond_destroy(&app->start_cond);
		pthread_mutex_destroy(&app->app_mutex);
		free(app);
		return (NULL);
	}
	app->dongles = init_dongles(app->args->nb_coders, app->args->scheduler);
	app->coders = init_coders(app);
	if (app->coders == NULL)
		return (free_app(app));
	mutex_print(&app->app_mutex, NULL, -1);
	return (app);
}
