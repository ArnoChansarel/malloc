/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansar <achansar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 09:30:16 by achansar          #+#    #+#             */
/*   Updated: 2022/10/17 15:27:23 by achansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	len_check;
	size_t	len_s;

	substr = NULL;
	if (!s)
		return (0);
	len_s = ft_strlen(s);
	len_check = 0;
	if (len_s > start)
	{
		while (len_check < len && s[start + len_check])
			len_check++;
	}
	substr = malloc((len_check + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	if (start > len_s)
		start = len_s - 1 + (len_s == 0);
	ft_strlcpy(substr, s + start, len_check + 1);
	return (substr);
}
