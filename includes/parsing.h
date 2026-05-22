/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kayzzel <gabach@student.42lyon.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 10:33:32 by kayzzel           #+#    #+#             */
/*   Updated: 2026/05/22 12:53:03 by kayzzel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

// STRUCTS

typedef struct s_args
{
	int		nb_coders;
	int		time_to_burnout;
	int		time_to_compile;
	int		time_to_debug;
	int		time_to_refactor;
	int		number_of_compiles_required;
	int		dongle_cooldown;
	char	scheduler[5];
}	t_args;

// FUNCS

int	parsing(t_args *args, int argc, char **argv);

#endif
