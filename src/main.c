/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <gabach@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 10:27:26 by gabach            #+#    #+#             */
/*   Updated: 2026/05/22 12:53:21 by kayzzel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	main(int argc, char **argv)
{
	static t_args	args = {0};

	if (parsing(&args, argc - 1, argv + 1))
		return (1);
	return (0);
}
