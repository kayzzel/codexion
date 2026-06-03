/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 13:20:37 by gabach            #+#    #+#             */
/*   Updated: 2026/06/03 13:30:37 by gabach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"
#include <pthread.h>

void	*coder_main_loop(t_coder *coder)
{
	return (NULL);
}

void	*coder_thread_init(void	*coder_ptr)
{
	t_coder	*coder;

	coder = (t_coder *)coder_ptr;
	pthread_cond_wait(&coder->start_cond, NULL);
	coder_main_loop(coder);
	return (NULL);
}
