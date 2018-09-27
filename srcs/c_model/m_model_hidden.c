/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_model_hidden.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 18:43:24 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/26 18:22:59 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool			m_model_hidden_setup(t_scene *scene)
{
	t_model *model;

	if (!(model = m_model_load(scene, scene->m_model_hidden,
								"./ressources/arrow.obj", "arrow")))
		return (m_model_destruct(&scene->m_model_hidden));
	if (!(model = m_model_load(scene, scene->m_model_hidden,
								"./ressources/cube.obj", "cube")))
		return (m_model_destruct(&scene->m_model_hidden));
	model->scaling = vector_construct(0.1f, 0.1f, 0.1f);
	model->same_scaling = 0.1f;
	if (!(model = m_model_load(scene, scene->m_model_hidden,
								"./ressources/plan2.obj", "plan")))
		return (m_model_destruct(&scene->m_model_hidden));
	return (true);
}
