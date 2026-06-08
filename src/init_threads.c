/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 13:08:28 by gabach            #+#    #+#             */
/*   Updated: 2026/06/08 13:35:00 by gabach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "coders.h"
#include "exit.h"

#include <pthread.h>
#include <stdlib.h>

int	init_monitoring_thread(t_app *app)
{
	(void)app;
	return (0);
}

int	init_coder_treads(t_app *app, pthread_t *threads)
{
	int			index;

	index = 0;
	while (index < app->args->nb_coders)
	{
		if (pthread_create(
				&threads[index], NULL, &coder_thread_init, &app->coders[index]
			))
		{
			return (1);
		}
		index++;
	}
	return (0);
}

int	init_treads(t_app *app)
{
	pthread_t	*coders_threads;

	coders_threads = malloc(sizeof(pthread_t) * app->args->nb_coders);
	if (coders_threads == NULL)
	{
		free_app(app);
		return (1);
	}
	if (init_coder_treads(app, coders_threads) == 1)
	{
		exit_threads(app, coders_threads);
		return (1);
	}
	if (init_monitoring_thread(app) == 1)
	{
		exit_threads(app, coders_threads);
		return (1);
	}
	return (0);
}
