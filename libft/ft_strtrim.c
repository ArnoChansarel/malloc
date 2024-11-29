/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansar <achansar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:45:04 by achansar          #+#    #+#             */
/*   Updated: 2022/10/17 14:28:33 by achansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ischarset(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	ft_lentrim(char *s1, char *set)
{
	int	i;
	int	l;

	i = 0;
	while (s1[i] != '\0')
	{
		if (ft_ischarset(s1[i], set) == 0)
			break ;
		i++;
	}
	l = ft_strlen(s1) - 1;
	while (l >= i)
	{
		if (ft_ischarset(s1[l], set) == 0)
			break ;
		l--;
	}
	return (l - i + 1);
}

static char	*ft_clean(char *s1, char *set, int size)
{
	int		i;
	int		j;
	int		k;
	char	*clean;

	i = 0;
	clean = malloc((size + 1) * sizeof(char));
	if (!clean)
		return (0);
	while (s1[i] != '\0')
	{
		if (ft_ischarset(s1[i], set) == 0)
			break ;
		i++;
	}
	j = i;
	k = 0;
	while (j < i + size)
	{
		clean[k++] = s1[j++];
	}
	clean[k] = '\0';
	return (clean);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		size;
	char	*clean;
	char	*ch_set;
	char	*ch_s1;

	if (!s1 || !set)
		return (0);
	ch_set = (char *) set;
	ch_s1 = (char *) s1;
	size = ft_lentrim(ch_s1, ch_set);
	i = 0;
	clean = ft_clean(ch_s1, ch_set, size);
	return (clean);
}
