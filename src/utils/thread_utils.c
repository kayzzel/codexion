/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 14:29:42 by gabach            #+#    #+#             */
/*   Updated: 2026/06/16 14:50:00 by gabach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "utils.h"

#include <pthread.h>

int	program_ended(t_app *app)
{
	pthread_mutex_lock(&app->app_mutex);
	if (app->end)
	{
		pthread_mutex_unlock(&app->app_mutex);
		return (1);
	}
	pthread_mutex_unlock(&app->app_mutex);
	return (0);
}
