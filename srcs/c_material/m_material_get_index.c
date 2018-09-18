/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_material_get_index.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 16:12:02 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/18 18:38:40 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int				m_material_get_index(t_m_material *m_material, char *str)
{
	unsigned int i;

	if (!str || !(*str))
		return (0);
	i = 0;
	while (i < m_material->size)
	{
		if (!strcmp(m_material->material[i]->name, str))
			return (i);
		i++;
	}
	return (0);
}
