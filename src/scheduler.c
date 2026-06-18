/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 11:21:22 by gabach            #+#    #+#             */
/*   Updated: 2026/06/18 14:50:22 by gabach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scheduler.h"
#include "coders.h"
#include "codexion.h"
#include "utils.h"

#include <pthread.h>
#include <unistd.h>

void	fifo(t_coder *coder, t_coder *heap_queue[2])
{
	if ((heap_queue[0] != NULL && heap_queue[0]->id == coder->id)
		|| (heap_queue[1] != NULL && heap_queue[1]->id == coder->id))
		return ;
	if (heap_queue[0] == NULL)
		heap_queue[0] = coder;
	else
		heap_queue[1] = coder;
}

void	edf(t_coder *coder, t_coder *heap_queue[2])
{
	if ((heap_queue[0] != NULL && heap_queue[0]->id == coder->id)
		|| (heap_queue[1] != NULL && heap_queue[1]->id == coder->id))
		return ;
	if (heap_queue[0] == NULL)
	{
		heap_queue[0] = coder;
		return ;
	}
	if (heap_queue[0]->last_compile > coder->last_compile)
	{
		heap_queue[1] = heap_queue[0];
		heap_queue[0] = coder;
	}
	else
		heap_queue[1] = coder;
}

void	remove_coder(int coder_id, t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mutex);
	if (dongle->heap_queue[0] != NULL && dongle->heap_queue[0]->id == coder_id)
		dongle->heap_queue[0] = dongle->heap_queue[1];
	dongle->heap_queue[1] = NULL;
	pthread_mutex_unlock(&dongle->mutex);
}

int	scheduler(t_coder *coder, t_dongle *dongle)
{
	if (dongle == NULL)
		return (0);
	pthread_mutex_lock(&dongle->mutex);
	dongle->heap_manager(coder, dongle->heap_queue);
	if (
		get_time_usec() / 1000
		< dongle->last_compile + coder->infos->dongle_cooldown
	)
	{
		pthread_mutex_unlock(&dongle->mutex);
		return (-1);
	}
	if (dongle->heap_queue[0]->id != coder->id || dongle->held == 1)
	{
		pthread_mutex_unlock(&dongle->mutex);
		return (0);
	}
	dongle->held = 1;
	pthread_mutex_unlock(&dongle->mutex);
	remove_coder(coder->id, dongle);
	return (1);
}

int	get_dongle(t_coder *coder, t_dongle *dongle, t_app *app)
{
	int	scheduler_return;
	int	cooldown_remaining;

	scheduler_return = 0;
	while (scheduler_return != 1)
	{
		scheduler_return = scheduler(coder, dongle);
		if (scheduler_return == -1)
		{
			cooldown_remaining = (dongle->last_compile
					+ app->args->dongle_cooldown - (get_time_usec() / 1000));
			if (msleep(cooldown_remaining, app))
				return (1);
		}
		else if (scheduler_return != 1)
			usleep(200);
		if (program_ended(app))
			return (1);
	}
	return (program_ended(app));
}
