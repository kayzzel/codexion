/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 11:25:38 by gabach            #+#    #+#             */
/*   Updated: 2026/06/16 11:25:45 by gabach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

#include <string.h>

int	is_positive_int(char *nbr)
{
	int		index;
	char	*comp;
	int		is_sign;

	index = 0;
	if (strcmp(nbr, "-0") == 0)
		return (1);
	while (nbr[index] != '\0')
	{
		if (nbr[index] < '0' || nbr[index] > '9')
			return (0);
		index++;
	}
	index = 0;
	is_sign = 0;
	comp = "2147483647";
	if (nbr[0] == '-' || strlen(nbr) - is_sign > 10)
		return (0);
	if (nbr[0] == '+')
		is_sign = 1;
	if (strlen(nbr) - is_sign < 10)
		return (1);
	while (nbr[index + is_sign] == comp[index])
		index++;
	return (nbr[index + is_sign] <= comp[index]);
}
