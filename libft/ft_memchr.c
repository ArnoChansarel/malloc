/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansar <achansar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 09:30:44 by achansar          #+#    #+#             */
/*   Updated: 2022/10/17 15:23:50 by achansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ch_s;
	unsigned char	ch_c;

	i = 0;
	ch_s = (unsigned char *) s;
	ch_c = (unsigned char) c;
	while (i < n)
	{
		if (ch_s[i] == ch_c)
		{
			return (&ch_s[i]);
		}
		i++;
	}
	return (NULL);
}
