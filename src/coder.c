/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 13:20:37 by gabach            #+#    #+#             */
/*   Updated: 2026/06/11 13:55:18 by gabach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"
#include "utils.h"

#include <pthread.h>
#include <time.h>

void	*coder_main_loop(t_coder *coder)
{
	mutex_print(NULL, "coder init", coder->id);
	return (NULL);
}

void	*coder_thread_init(void	*coder_ptr)
{
	t_coder	*coder;

	coder = (t_coder *)coder_ptr;
	pthread_mutex_lock(&coder->left_dongle->mutex);
	while (*coder->init == 0)
		pthread_cond_wait(coder->start_cond, &coder->left_dongle->mutex);
	pthread_mutex_unlock(&coder->left_dongle->mutex);
	if (*coder->init == -1)
		return (NULL);
	coder_main_loop(coder);
	return (NULL);
}
