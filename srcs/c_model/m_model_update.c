/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_model_update.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 00:24:08 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/25 20:13:16 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	m_model_update(t_m_model *m_model)
{
	t_model *model;
	size_t	i;

	i = 0;
	while (i < m_model->size)
	{
		model = m_model->model[i];
		if (model->flag & MODEL_ROTATE)
		{
			model->update = true;
			model->rotation.y += 0.01f;
		}
		i++;
	}
}
