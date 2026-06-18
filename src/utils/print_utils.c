/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 11:23:06 by gabach            #+#    #+#             */
/*   Updated: 2026/06/18 16:01:48 by gabach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

#include <pthread.h>
#include <stdio.h>

int	init_mutex_print(pthread_mutex_t *mutex)
{
	return (mutex_print(mutex, NULL, -1));
}

int	stop_mutex_print(void)
{
	return (mutex_print(NULL, NULL, -1));
}

int	thread_print(char *str, int coder_id)
{
	return (mutex_print(NULL, str, coder_id));
}

int	mutex_print(
		pthread_mutex_t *mutex,
		char *str,
		int coder_id
	)
{
	static pthread_mutex_t	*str_mutex = NULL;
	int						time;

	if (str_mutex == NULL)
	{
		if (mutex == NULL)
			return (1);
		str_mutex = mutex;
		return (0);
	}
	if (coder_id == -1)
	{
		str_mutex = NULL;
		return (0);
	}
	pthread_mutex_lock(str_mutex);
	time = get_time_msec();
	printf("%i %i %s\n", time, coder_id, str);
	pthread_mutex_unlock(str_mutex);
	return (0);
}
