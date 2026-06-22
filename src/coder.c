/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 13:20:37 by gabach            #+#    #+#             */
/*   Updated: 2026/06/22 13:58:06 by gabach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"
#include "codexion.h"
#include "scheduler.h"
#include "utils.h"

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int	get_dongles(t_coder *coder, t_app *app)
{
	t_dongle	*f_dgl;
	t_dongle	*s_dgl;

	f_dgl = coder->left_dongle;
	s_dgl = coder->right_dongle;
	if (coder->id % 2 == 0)
	{
		f_dgl = coder->right_dongle;
		s_dgl = coder->left_dongle;
	}
	if (f_dgl != NULL)
		f_dgl->heap_manager(coder, f_dgl->heap_queue, &f_dgl->mutex);
	if (s_dgl != NULL)
		s_dgl->heap_manager(coder, s_dgl->heap_queue, &s_dgl->mutex);
	if (get_dongle(coder, f_dgl, app))
		return (1);
	else
		thread_print("has taken a dongle", coder->id);
	if (get_dongle(coder, s_dgl, app))
		return (1);
	else
		thread_print("has taken a dongle", coder->id);
	return (program_ended(app));
}

int	coder_compile(t_coder *coder, t_app *app)
{
	if (get_dongles(coder, app))
		return (1);
	pthread_mutex_lock(&coder->mutex);
	coder->nb_compile++;
	coder->last_compile = get_time_msec();
	pthread_mutex_unlock(&coder->mutex);
	if (program_ended(app))
		return (1);
	thread_print("is compiling", coder->id);
	if (msleep(app->args->time_to_compile, app))
		return (1);
	pthread_mutex_lock(&coder->left_dongle->mutex);
	coder->left_dongle->last_compile = get_time_msec();
	coder->left_dongle->held = 0;
	pthread_mutex_unlock(&coder->left_dongle->mutex);
	if (program_ended(app))
		return (1);
	pthread_mutex_lock(&coder->right_dongle->mutex);
	coder->right_dongle->last_compile = get_time_msec();
	coder->right_dongle->held = 0;
	pthread_mutex_unlock(&coder->right_dongle->mutex);
	return (program_ended(app));
}

void	*coder_main_loop(t_coder *coder, t_app *app)
{
	while (program_ended(app) == 0)
	{
		if (coder_compile(coder, app))
			return (NULL);
		thread_print("is debugging", coder->id);
		if (program_ended(app))
			return (NULL);
		if (msleep(app->args->time_to_debug, app))
			return (NULL);
		thread_print("is refactoring", coder->id);
		if (msleep(app->args->time_to_refactor, app))
			return (NULL);
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
	if (coder->id % 2 == 1)
		if (msleep(coder->infos->time_to_compile, app))
			return (NULL);
	coder_main_loop(coder, app);
	return (NULL);
}
