/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansar <achansar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:56:13 by achansar          #+#    #+#             */
/*   Updated: 2022/10/14 17:52:28 by achansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*rtr;
	char	*char_s;
	char	ch_c;

	i = 0;
	rtr = NULL;
	char_s = (char *) s;
	ch_c = (char) c;
	if (ch_c == '\0')
		return (&char_s[ft_strlen(char_s)]);
	while (char_s[i] != '\0')
	{
		if (char_s[i] == ch_c)
		{
			rtr = &char_s[i];
		}
		i++;
	}
	return (rtr);
}
