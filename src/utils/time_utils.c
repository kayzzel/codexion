/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 11:24:24 by gabach            #+#    #+#             */
/*   Updated: 2026/06/18 16:16:02 by gabach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "codexion.h"

#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

void	init_time(void)
{
	get_time_msec();
}

int	get_time_msec(void)
{
	static int		start_time = -1;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (start_time == -1)
		start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000) - start_time);
}

int	msleep(int msec, t_app *app)
{
	int	time_goal;

	time_goal = get_time_msec() + msec;
	while (time_goal > get_time_msec())
	{
		if (program_ended(app))
			return (1);
		usleep(100);
	}
	return (program_ended(app));
}
