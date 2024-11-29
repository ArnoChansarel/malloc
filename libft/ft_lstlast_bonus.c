/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansar <achansar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:05:53 by achansar          #+#    #+#             */
/*   Updated: 2022/10/17 15:30:20 by achansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	int	s;
	int	i;

	if (!lst)
		return (0);
	i = 0;
	s = ft_lstsize(lst);
	while (lst && i < s - 1)
	{
		lst = lst->next;
		i++;
	}
	return (lst);
}
