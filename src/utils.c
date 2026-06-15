/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <gabach@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 12:34:22 by gabach            #+#    #+#             */
/*   Updated: 2026/06/15 22:57:25 by kayzzel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "codexion.h"

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

int	is_positive_int(char *nbr)
{
	int		index;
	char	*comp;
	int		is_sign;

	index = 0;
	if (strcmp(nbr, "-0") == 0)
		return (1);
	while (nbr[index] != '\0')
	{
		if (nbr[index] < '0' || nbr[index] > '9')
			return (0);
		index++;
	}
	index = 0;
	is_sign = 0;
	comp = "2147483647";
	if (nbr[0] == '-' || strlen(nbr) - is_sign > 10)
		return (0);
	if (nbr[0] == '+')
		is_sign = 1;
	if (strlen(nbr) - is_sign < 10)
		return (1);
	while (nbr[index + is_sign] == comp[index])
		index++;
	return (nbr[index + is_sign] <= comp[index]);
}

void	mutex_print(
		pthread_mutex_t *mutex,
		char *str,
		int coder_id
	)
{
	static pthread_mutex_t	*str_mutex = NULL;
	int						time;

	if (str_mutex == NULL)
	{
		str_mutex = mutex;
		return ;
	}
	pthread_mutex_lock(str_mutex);
	time = get_time_usec() / 1000;
	if (coder_id == -1)
		printf("%s\n", str);
	else
		printf("%i %i %s\n", time, coder_id, str);
	pthread_mutex_unlock(str_mutex);
}

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

	total_usec = 0;
	us_loop = 100;
	while (total_usec * 1000 < msec)
	{
		if (app->end == 1)
			return (1);
		usleep(us_loop);
		total_usec += us_loop;
	}
	return (app->end);
}
