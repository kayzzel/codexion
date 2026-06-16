/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 11:24:24 by gabach            #+#    #+#             */
/*   Updated: 2026/06/16 17:35:31 by gabach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "codexion.h"

#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

void	init_time(void)
{
	get_time_usec();
}

int	get_time_usec(void)
{
	static int		start_time = -1;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (start_time == -1)
		start_time = tv.tv_sec * 1000000 + tv.tv_usec;
	return ((tv.tv_sec * 1000000 + tv.tv_usec) - start_time);
}

int	msleep(int msec, t_app *app)
{
	int	time_goal;
	int	return_value;

	time_goal = get_time_usec() + msec * 1000;
	while (time_goal > get_time_usec())
	{
		pthread_mutex_lock(&app->app_mutex);
		if (app->end == 1)
		{
			pthread_mutex_unlock(&app->app_mutex);
			return (1);
		}
		pthread_mutex_unlock(&app->app_mutex);
		usleep(100);
	}
	pthread_mutex_lock(&app->app_mutex);
	return_value = app->end;
	pthread_mutex_unlock(&app->app_mutex);
	return (return_value);
}
