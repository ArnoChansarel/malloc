/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansar <achansar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:40:14 by achansar          #+#    #+#             */
/*   Updated: 2022/10/17 13:07:41 by achansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*char_s;
	char	ch_c;

	i = 0;
	char_s = (char *) s;
	ch_c = (char) c;
	while (char_s[i] != '\0')
	{
		if (char_s[i] == ch_c)
		{
			return (&char_s[i]);
		}
		i++;
	}
	if (char_s[i] == ch_c)
		return (&char_s[i]);
	return (0);
}
