/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <gabach@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 10:41:11 by gabach            #+#    #+#             */
/*   Updated: 2026/06/18 15:32:29 by gabach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static t_args	*print_parsing_error(int error)
{
	printf("Args Parsing Error: ");
	if (error == -1)
		printf("Program must get exactly 8 arg\n");
	if (error == 0)
		printf("The number of coders must be an int > 0\n");
	if (error == 1)
		printf("The time to burnout must be an int >= 0\n");
	if (error == 2)
		printf("The time to compile must be an int >= 0\n");
	if (error == 3)
		printf("The time to debug must be an int >= 0\n");
	if (error == 4)
		printf("The time to refactor must be an int >= 0\n");
	if (error == 5)
		printf("The number of compile needed must be an int >= 0\n");
	if (error == 6)
		printf("The dongle cooldown must be an int >= 0\n");
	if (error == 7)
		printf("The scheduler must be \"fifo\" or \"edf\"\n");
	printf("usage: ./codexion number_of_coders time_to_burnout \
time_to_compile time_to_debug time_to_refactor \
number_of_compiles_required dongle_cooldown schedule\n");
	return (NULL);
}

static int	get_coder_info(t_args *args, char **argv)
{
	int	index;

	if (!is_positive_int(argv[0]) || atoi(argv[0]) == 0)
		return (0);
	index = 1;
	while (index < 6)
	{
		if (!is_positive_int(argv[index]))
			return (index);
		index++;
	}
	args->nb_coders = atoi(argv[0]);
	args->time_to_burnout = atoi(argv[1]);
	args->time_to_compile = atoi(argv[2]);
	args->time_to_debug = atoi(argv[3]);
	args->time_to_refactor = atoi(argv[4]);
	args->number_of_compiles_required = atoi(argv[5]);
	return (-1);
}

static int	get_dongle_info(t_args *args, char **argv)
{
	if (!is_positive_int(argv[6]))
		return (6);
	args->dongle_cooldown = atoi(argv[6]);
	if (strcmp(argv[7], "edf") == 0)
	{
		args->scheduler[0] = 'e';
		args->scheduler[1] = 'd';
		args->scheduler[2] = 'f';
		args->scheduler[3] = '\0';
	}
	else if (strcmp(argv[7], "fifo") == 0)
	{
		args->scheduler[0] = 'f';
		args->scheduler[1] = 'i';
		args->scheduler[2] = 'f';
		args->scheduler[3] = 'o';
		args->scheduler[4] = '\0';
	}
	else
		return (7);
	return (-1);
}

t_args	*parsing(int argc, char **argv)
{
	t_args	*args;
	int		error;

	args = malloc(sizeof(t_args));
	if (args == NULL)
		return (NULL);
	if (argc != 8)
	{
		free(args);
		return (print_parsing_error(-1));
	}
	error = get_coder_info(args, argv);
	if (error != -1)
	{
		free(args);
		return (print_parsing_error(error));
	}
	error = get_dongle_info(args, argv);
	if (error != -1)
	{
		free(args);
		return (print_parsing_error(error));
	}
	return (args);
}
