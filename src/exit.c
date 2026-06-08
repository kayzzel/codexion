/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <gabach@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:43:22 by gabach            #+#    #+#             */
/*   Updated: 2026/06/08 13:36:58 by gabach           ###   ########.fr       */
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
		pthread_cond_destroy(&dongles[index]->cond);
		free(dongles[index]);
		dongles[index] = NULL;
		index++;
	}
	free(dongles);
	dongles = NULL;
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
	coders = NULL;
	return (NULL);
}

t_app	*free_app(t_app *app)
{
	if (app == NULL)
		return (NULL);
	if (app->args == NULL)
	{
		pthread_cond_destroy(&app->start_cond);
		pthread_mutex_destroy(&app->print_mutex);
		free(app);
		return (NULL);
	}
	free(app->args);
	if (app->dongles != NULL)
		free_dongles(app->dongles);
	if (app->coders != NULL)
		free_coders(app->coders);
	pthread_cond_destroy(&app->start_cond);
	pthread_mutex_destroy(&app->print_mutex);
	free(app);
	return (NULL);
}

void	exit_threads(t_app *app, pthread_t *coders_threads)
{
	int	index;

	index = 0;
	app->init = 0;
	pthread_cond_broadcast(&app->start_cond);
	while (index < app->args->nb_coders)
	{
		pthread_join(coders_threads[index], NULL);
		index++;
	}
	free(coders_threads);
	free_app(app);
}
