/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 20:08:58 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/11/13 22:11:53 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memrealloc(void *ptr, size_t size_old, size_t size_new)
{
	void	*new_ptr;

	if (!(new_ptr = ft_memalloc(size_new)))
		return (NULL);
	if (ptr)
		new_ptr = ft_memcpy(new_ptr, ptr, size_old);
	if (ptr)
		free(ptr);
	return (new_ptr);
}
