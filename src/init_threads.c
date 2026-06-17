/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 13:08:28 by gabach            #+#    #+#             */
/*   Updated: 2026/06/17 18:07:49 by gabach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "coders.h"
#include "exit.h"
#include "monitor.h"

#include <pthread.h>
#include <stdlib.h>

int	init_monitoring_thread(t_app *app)
{
	pthread_t	monitor_thread;

	if (pthread_create(&monitor_thread, NULL, &monitor_thread_init, app) != 0)
		return (1);
	pthread_join(monitor_thread, NULL);
	return (0);
}

int	init_coder_treads(t_app *app, pthread_t *threads)
{
	int				index;
	t_coder_pth_arg	*arg;

	index = 0;
	while (index < app->args->nb_coders)
	{
		arg = malloc(sizeof(t_coder_pth_arg));
		if (arg == NULL)
			return (index);
		arg->app = app;
		arg->coder = app->coders[index];
		if (pthread_create(&threads[index], NULL, &coder_thread_init, arg) != 0)
		{
			free(arg);
			return (index);
		}
		index++;
	}
	return (index);
}

int	init_treads(t_app *app)
{
	pthread_t	*coders_threads;
	int			created_threads;

	coders_threads = malloc(sizeof(pthread_t) * app->args->nb_coders);
	if (coders_threads == NULL)
	{
		free_app(app);
		return (1);
	}
	created_threads = init_coder_treads(app, coders_threads);
	if (created_threads != app->args->nb_coders)
	{
		exit_threads(app, created_threads, coders_threads);
		return (1);
	}
	app->coder_threads = coders_threads;
	if (init_monitoring_thread(app) == 1)
	{
		exit_threads(app, created_threads, coders_threads);
		return (1);
	}
	free(coders_threads);
	return (0);
}
