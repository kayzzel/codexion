/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 11:24:24 by gabach            #+#    #+#             */
/*   Updated: 2026/06/17 10:53:50 by gabach           ###   ########.fr       */
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

	time_goal = get_time_usec() + msec * 1000;
	while (time_goal > get_time_usec())
	{
		if (program_ended(app))
			return (1);
		usleep(100);
	}
	return (program_ended(app));
}
