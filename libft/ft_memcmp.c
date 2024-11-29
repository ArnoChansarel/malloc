/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansar <achansar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 09:27:24 by achansar          #+#    #+#             */
/*   Updated: 2022/10/17 15:22:45 by achansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*ch_s1;
	unsigned char	*ch_s2;

	if (n == 0)
		return (0);
	ch_s1 = (unsigned char *) s1;
	ch_s2 = (unsigned char *) s2;
	i = 0;
	while (ch_s1[i] == ch_s2[i] && i < n - 1)
	{
		i++;
	}
	return ((int)(ch_s1[i] - ch_s2[i]));
}
