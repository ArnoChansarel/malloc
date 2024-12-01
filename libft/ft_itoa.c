/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansar <achansar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 09:26:41 by achansar          #+#    #+#             */
/*   Updated: 2022/10/17 13:05:03 by achansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(long n)
{
	int	l;

	l = 0;
	if (n == 0)
		l = 1;
	else if (n < 0)
	{
		n = -n;
		l++;
	}
	while (n > 0)
	{
		n = n / 10;
		l++;
	}
	return (l);
}

char	*ft_itoa(int n)
{
	int		size;
	char	*tab;
	long	nb;

	nb = (long) n;
	size = ft_intlen(nb);
	tab = malloc((size + 1) * sizeof(char));
	if (!tab)
		return (0);
	tab[size--] = '\0';
	if (nb < 0)
		nb = -nb;
	while (size >= 0)
	{
		tab[size] = nb % 10 + 48;
		nb = nb / 10;
		size--;
	}
	if (n < 0)
		tab[0] = '-';
	return (tab);
}