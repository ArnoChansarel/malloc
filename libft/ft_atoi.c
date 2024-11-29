/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansar <achansar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:20:50 by achansar          #+#    #+#             */
/*   Updated: 2022/10/17 15:24:11 by achansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	size_t	convert;

	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] == '0')
		i++;
	convert = 0;
	while (str[i] >= 48 && str[i] <= 57)
	{
		convert = convert * 10 + str[i++] - 48;
		if ((convert > 9223372036854775807) && sign == -1)
			return (0);
		else if ((convert > 9223372036854775807) && sign == 1)
			return (-1);
	}
	return (convert * sign);
}
