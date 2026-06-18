/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <gabach@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:43:22 by gabach            #+#    #+#             */
/*   Updated: 2026/06/18 15:45:15 by gabach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"
#include "codexion.h"

#include <pthread.h>
#include <stdlib.h>

char	*free_dongles(t_dongle **dongles)
{
	int	index;

	if (dongles == NULL)
		return (NULL);
	index = 0;
	while (dongles[index])
	{
		pthread_mutex_destroy(&dongles[index]->mutex);
		free(dongles[index]);
		index++;
	}
	free(dongles);
	return (NULL);
}

char	*free_coders(t_coder **coders)
{
	int	index;

	if (coders == NULL)
		return (NULL);
	index = 0;
	while (coders[index])
	{
		free(coders[index]);
		coders[index] = NULL;
		index++;
	}
	free(coders);
	return (NULL);
}

t_app	*free_app(t_app *app)
{
	if (app == NULL)
		return (NULL);
	if (app->args == NULL)
	{
		pthread_cond_destroy(&app->start_cond);
		pthread_mutex_destroy(&app->app_mutex);
		free(app);
		return (NULL);
	}
	free(app->args);
	if (app->dongles != NULL)
		free_dongles(app->dongles);
	if (app->coders != NULL)
		free_coders(app->coders);
	pthread_cond_destroy(&app->start_cond);
	pthread_mutex_destroy(&app->app_mutex);
	free(app);
	return (NULL);
}

int	test_mutex_cond_init(t_app *app, int cond_init, int mutex_init)
{
	if (mutex_init && cond_init)
		return (1);
	if (cond_init)
		pthread_cond_destroy(&app->start_cond);
	if (mutex_init)
		pthread_mutex_destroy(&app->app_mutex);
	free(app);
	return (0);
}

void	exit_threads(t_app *app, int nb_created, pthread_t *coders_threads)
{
	int	index;

	index = 0;
	app->init = -1;
	if (coders_threads == NULL)
	{
		free_app(app);
		return ;
	}
	pthread_cond_broadcast(&app->start_cond);
	while (index < nb_created)
	{
		pthread_join(coders_threads[index], NULL);
		index++;
	}
	free(coders_threads);
	free_app(app);
}
