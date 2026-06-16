/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 11:24:24 by gabach            #+#    #+#             */
/*   Updated: 2026/06/16 14:24:23 by gabach           ###   ########.fr       */
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
	int	total_usec;
	int	us_loop;
	int	return_value;

	total_usec = 0;
	us_loop = 500;
	while (total_usec / 1000 < msec)
	{
		if (total_usec % 3000 == 1)
		{
			pthread_mutex_lock(&app->app_mutex);
			if (app->end == 1)
			{
				pthread_mutex_unlock(&app->app_mutex);
				return (1);
			}
			pthread_mutex_unlock(&app->app_mutex);
		}
		usleep(us_loop);
		total_usec += us_loop;
	}
	pthread_mutex_lock(&app->app_mutex);
	return_value = app->end;
	pthread_mutex_unlock(&app->app_mutex);
	return (return_value);
}
