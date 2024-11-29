/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansar <achansar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 09:46:30 by achansar          #+#    #+#             */
/*   Updated: 2022/10/14 17:52:00 by achansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	l;
	size_t	lcpy;

	if (!dst && dstsize == 0)
		return (ft_strlen(src));
	l = 0;
	while (*dst != '\0' && l < dstsize && dstsize > 0)
	{
		dst++;
		l++;
	}
	lcpy = ft_strlcpy(dst, src, dstsize - l);
	return (l + lcpy);
}
