/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansar <achansar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 17:57:35 by achansar          #+#    #+#             */
/*   Updated: 2022/10/14 11:16:24 by achansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*rtr;
	t_list	*tmp;

	if (!lst || !f || !del)
		return (0);
	rtr = ft_lstnew((*f)(lst->content));
	if (!rtr)
		ft_lstdelone(rtr, del);
	lst = lst->next;
	while (lst)
	{
		tmp = ft_lstnew((*f)(lst->content));
		if (!tmp)
		{
			ft_lstclear(&rtr, del);
			return (0);
		}
		ft_lstadd_back(&rtr, tmp);
		lst = lst->next;
	}
	return (rtr);
}
