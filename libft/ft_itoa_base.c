/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansar <achansar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:38:18 by achansar          #+#    #+#             */
/*   Updated: 2022/10/14 17:52:09 by achansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_itoa_base(size_t nb, char base, char length, bool prefix)
{
	char	*str;

	str = "0123456789ABCDEFGHIJKLMNOPQRSTUIVWXYZ";
	if (nb / base)
		ft_itoa_base(nb / base, base, length - 1, prefix);
	else
	{
		if (prefix)
			ft_putstr("0x");
		while (--length > 0)
		{
			ft_putstr("0");
		}
	}
	write(1, &str[nb % base], 1);
}