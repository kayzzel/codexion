/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 11:48:53 by gabach            #+#    #+#             */
/*   Updated: 2026/06/16 14:37:32 by gabach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor.h"
#include "codexion.h"
#include "utils.h"

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void	wait_coders_end(t_app *app)
{
	int	index;

	index = 0;
	while (index < app->args->nb_coders)
	{
		pthread_join(app->coder_threads[index], NULL);
		index++;
	}
}

int	is_burnout(t_app *app)
{
	int	index;
	int	burnout;

	index = 0;
	burnout = get_time_usec() / 1000 - app->args->time_to_burnout;
	while (index < app->args->nb_coders)
	{
		pthread_mutex_lock(&app->coders[index]->mutex);
		if (app->coders[index]->last_compile <= burnout)
		{
			pthread_mutex_unlock(&app->coders[index]->mutex);
			pthread_mutex_lock(&app->app_mutex);
			app->end = 1;
			pthread_mutex_unlock(&app->app_mutex);
			thread_print("burned out", index + 1);
			// stop_mutex_print();
			return (1);
		}
		pthread_mutex_unlock(&app->coders[index]->mutex);
		index++;
	}
	return (0);
}

int	end_compiles(t_app *app)
{
	int	index;
	int	compiled;
	int	compile_required;

	index = 0;
	compiled = 0;
	compile_required = app->args->number_of_compiles_required;
	while (index < app->args->nb_coders)
	{
		pthread_mutex_lock(&app->coders[index]->mutex);
		if (app->coders[index]->nb_compile >= compile_required)
			compiled++;
		pthread_mutex_unlock(&app->coders[index]->mutex);
		index++;
	}
	if (compiled == app->args->nb_coders)
	{
		app->end = 1;
		return (1);
	}
	return (0);
}

void	*monitor_main_loop(t_app *app)
{
	while (app->end == 0)
	{
		if (is_burnout(app))
		{
			wait_coders_end(app);
			return (NULL);
		}
		if (end_compiles(app))
		{
			wait_coders_end(app);
			return (NULL);
		}
		usleep(500);
	}
	wait_coders_end(app);
	return (NULL);
}

void	*monitor_thread_init(void *app_ptr)
{
	t_app	*app;

	app = (t_app *)app_ptr;
	pthread_mutex_lock(&app->app_mutex);
	app->init = 1;
	pthread_mutex_unlock(&app->app_mutex);
	init_time();
	if (pthread_cond_broadcast(&app->start_cond) != 0)
		printf("monitor_thread_init\n");
	monitor_main_loop(app);
	return (NULL);
}
