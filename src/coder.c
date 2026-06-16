/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 13:20:37 by gabach            #+#    #+#             */
/*   Updated: 2026/06/16 17:36:56 by gabach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"
#include "codexion.h"
#include "utils.h"

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int	coder_compile(t_coder *coder, t_app *app)
{
	pthread_mutex_lock(&coder->mutex);
	coder->nb_compile++;
	coder->last_compile = get_time_usec() / 1000;
	pthread_mutex_unlock(&coder->mutex);
	if (program_ended(app))
		return (1);
	thread_print("is compiling", coder->id);
	if (program_ended(app))
		return (1);
	msleep(app->args->time_to_compile, app);
	return (program_ended(app));
}

void	*coder_main_loop(t_coder *coder, t_app *app)
{
	while (program_ended(app) == 0)
	{
		if (coder_compile(coder, app))
			return (NULL);
		thread_print("is debuging", coder->id);
		if (program_ended(app))
			return (NULL);
		msleep(app->args->time_to_debug, app);
		if (program_ended(app))
			return (NULL);
		thread_print("is refactoring", coder->id);
		if (program_ended(app))
			return (NULL);
		msleep(app->args->time_to_refactor, app);
	}
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
		pthread_cond_wait(&app->start_cond, &app->app_mutex);
	if (*coder->init == -1)
	{
		pthread_mutex_unlock(&app->app_mutex);
		return (NULL);
	}
	pthread_mutex_unlock(&app->app_mutex);
	coder_main_loop(coder, app);
	return (NULL);
}
