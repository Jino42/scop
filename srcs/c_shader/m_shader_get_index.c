/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_shader_get_index.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 16:26:26 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/07/17 16:30:55 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int				m_shader_get_index(t_m_shader *m_shader, char *str)
{
	unsigned int i;

	if (!str || !(*str))
		return (0);
	i = 0;
	while (i < m_shader->size)
	{
		if (!strcmp(m_shader->shader[i]->name, str))
			return (i);
		i++;
	}
	return (0);
}
