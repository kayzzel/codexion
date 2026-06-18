/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_app.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <gabach@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 16:48:35 by gabach            #+#    #+#             */
/*   Updated: 2026/06/18 13:16:20 by gabach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"
#include "exit.h"
#include "parsing.h"
#include "codexion.h"
#include "scheduler.h"
#include "utils.h"

#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

static t_dongle	*create_dongle(char scheduler[5], int cooldown)
{
	t_dongle	*dongle;
	void		(*func)(t_coder*, t_coder*[2]);

	dongle = malloc(sizeof(t_dongle));
	if (dongle == NULL)
		return (NULL);
	func = edf;
	if (strcmp(scheduler, "fifo") == 0)
		func = fifo;
	if (pthread_mutex_init(&dongle->mutex, NULL) != 0)
	{
		free(dongle);
		return (NULL);
	}
	dongle->held = 0;
	dongle->heap_manager = func;
	dongle->heap_queue[0] = NULL;
	dongle->heap_queue[1] = NULL;
	dongle->last_compile = -cooldown;
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
	coder->left_dongle = app->dongles[id - 1];
	coder->right_dongle = app->dongles[(id + nb_coders - 2) % nb_coders];
	if (app->args->nb_coders == 1)
		coder->right_dongle = NULL;
	coder->infos = app->args;
	coder->nb_compile = 0;
	coder->last_compile = 0;
	coder->init = &app->init;
	return (coder);
}

t_dongle	**init_dongles(t_app *app)
{
	t_dongle	**dongles;
	int			index;
	t_args		*args;

	args = app->args;
	dongles = malloc(sizeof(t_dongle *) * (args->nb_coders + 1));
	if (dongles == NULL)
		return (NULL);
	index = 0;
	while (index < args->nb_coders)
	{
		dongles[index] = create_dongle(args->scheduler, args->dongle_cooldown);
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
	if (!test_mutex_cond_init(app,
			pthread_cond_init(&app->start_cond, NULL) == 0,
			pthread_mutex_init(&app->app_mutex, NULL) == 0))
		return (NULL);
	app->args = parsing(argc - 1, argv + 1);
	if (app->args == NULL)
		return (free_app(app));
	app->dongles = init_dongles(app);
	app->coders = init_coders(app);
	if (app->coders == NULL)
		return (free_app(app));
	init_mutex_print(&app->app_mutex);
	return (app);
}
