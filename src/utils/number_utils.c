/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabach <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 11:25:38 by gabach            #+#    #+#             */
/*   Updated: 2026/06/18 15:30:44 by gabach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

#include <string.h>

static int	is_zero(char *number)
{
	if (number[0] == '-' || number[0] == '+')
		number++;
	while (number[0] == '0')
		number++;
	return (strlen(number) == 0);
}

static int	is_number_int(char *number)
{
	int		index;
	char	*comp;

	index = 0;
	comp = "2147483647";
	if (number[0] == '-')
		comp = "2147483648";
	if (number[index] == '-' || number[index] == '+')
		number++;
	while (number[0] == '0')
		number++;
	if (strlen(number) > 10)
		return (0);
	if (strlen(number) < 10)
		return (1);
	while (number[index] == comp[index])
		index++;
	return (number[index] <= comp[index]);
}

int	is_positive_int(char *nbr)
{
	int	index;

	index = 0;
	if (is_zero(nbr))
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
