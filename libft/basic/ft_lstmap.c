/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 16:14:27 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/11/08 14:23:29 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*status;
	t_list	*first;

	first = NULL;
	if (!lst || !f)
		return (NULL);
	while (lst)
	{
		new = (*f)(lst);
		if (!(new = ft_lstnew(new->content, new->content_size)))
			return (NULL);
		if (first)
		{
			status->next = new;
			status = new;
		}
		else
		{
			first = new;
			status = new;
		}
		lst = lst->next;
	}
	return (first);
}
