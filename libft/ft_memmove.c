/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansar <achansar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 09:28:13 by achansar          #+#    #+#             */
/*   Updated: 2022/10/14 17:50:55 by achansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	void	*rtr;

	if ((!dst) && (!src))
		return (dst);
	rtr = dst;
	if (src < dst)
	{
		dst += n;
		src += n;
		while (n--)
		{
			dst--;
			src--;
			*(char *)dst = *(char *)src;
		}
	}
	else
	{
		while (n--)
			*(char *)dst++ = *(char *)src++;
	}
	return (rtr);
}
