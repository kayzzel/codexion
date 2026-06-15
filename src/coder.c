/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 13:20:37 by gabach            #+#    #+#             */
/*   Updated: 2026/06/15 15:24:27 by gabach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"
#include "codexion.h"
#include "utils.h"

#include <pthread.h>
#include <stdlib.h>

void	*coder_main_loop(t_coder *coder, t_app *app)
{
	mutex_print(NULL, "coder init", coder->id);
	while (msleep(10, app) == 0)
		continue ;
	return (NULL);
}

void	*coder_thread_init(void	*arg_ptr)
{
	t_coder_pth_arg	*arg;
	t_app			*app;
	t_coder			*coder;

	arg = (t_coder_pth_arg *)arg_ptr;
	app = arg->app;
	coder = arg->coder;
	free(arg_ptr);
	pthread_mutex_lock(&app->app_mutex);
	while (*coder->init == 0)
		pthread_cond_wait(coder->start_cond, &app->app_mutex);
	pthread_mutex_unlock(&app->app_mutex);
	if (*coder->init == -1)
		return (NULL);
	coder_main_loop(coder, app);
	return (NULL);
}
