/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <gabach@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 12:34:22 by gabach            #+#    #+#             */
/*   Updated: 2026/06/03 14:04:44 by gabach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>

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

	if (str_mutex == NULL)
		str_mutex = mutex;
	pthread_mutex_lock(str_mutex);
	if (coder_id == -1)
		printf("%s", str);
	else
		printf("coder: %i, %s", coder_id, str);
	pthread_mutex_unlock(str_mutex);
}
