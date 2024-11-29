/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansar <achansar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 16:08:09 by achansar          #+#    #+#             */
/*   Updated: 2022/10/17 14:30:18 by achansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*rtr;

	if (!s || !f)
		return (0);
	rtr = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!rtr)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		rtr[i] = (*f)(i, s[i]);
		i++;
	}
	rtr[i] = '\0';
	return (rtr);
}
