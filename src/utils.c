/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <gabach@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 12:34:22 by gabach            #+#    #+#             */
/*   Updated: 2026/06/15 15:27:55 by gabach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "codexion.h"

#include <bits/types/struct_timeval.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

static int	is_number_int(char *number)
{
	int		index;
	int		is_sign;
	char	*comp;

	index = 0;
	is_sign = 0;
	comp = "2147483647";
	if (number[0] == '-')
		comp = "2147483648";
	if (number[index] == '-' || number[index] == '+')
		is_sign = 1;
	if (strlen(number) - is_sign > 10)
		return (0);
	if (strlen(number) - is_sign < 10)
		return (1);
	while (number[index + is_sign] == comp[index])
		index++;
	return (number[index + is_sign] <= comp[index]);
}

int	is_positive_int(char *nbr)
{
	int	index;

	index = 0;
	if (strcmp(nbr, "-0") == 0)
		return (1);
	while (nbr[index] != '\0')
	{
		if (nbr[index] < '0' || nbr[index] > '9')
			return (0);
		index++;
	}
	if (!is_number_int(nbr))
		return (0);
	return (1);
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
	time = get_time_usec();
	pthread_mutex_lock(str_mutex);
	if (coder_id == -1)
		printf("%s\n", str);
	else
		printf("%i %i %s\n", time, coder_id, str);
	pthread_mutex_unlock(str_mutex);
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
		total_usec = us_loop;
	}
	return (app->end);
}
