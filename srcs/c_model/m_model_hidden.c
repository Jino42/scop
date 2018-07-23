#include "scop.h"

bool			m_model_hidden_setup(t_scene *scene)
{
	t_model *model;

	if (!(model = m_model_load(scene, scene->m_model_hidden, "./ressources/arrow.obj", "arrow")))
		return (m_model_destruct(&scene->m_model_hidden));
	if (!(model = m_model_load(scene, scene->m_model_hidden, "./ressources/cube.obj", "cube")))
		return (m_model_destruct(&scene->m_model_hidden));
	model->scaling = vector_construct(0.1f, 0.1f, 0.1f);
	model->same_scaling = 0.1f;
	return (true);
}
