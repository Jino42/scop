/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 16:16:21 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/26 17:43:32 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void *tab;

	if (!(tab = malloc(size)))
		exit(0);
	if (tab == NULL)
		return (NULL);
	bzero(tab, size);
	return (tab);
}
