#include "scop.h"

t_scene		*scene_construct()
{
	t_scene *scene;

	if (!(scene = ft_memalloc(sizeof(t_scene))))
		return (NULL);
	scene->shader_add = &m_shader_add;
	scene->model_add = &m_model_add;
	scene->mesh_add = &m_mesh_add;
	if (!(scene->m_model = m_model_construct()))
		return (scene_destruct(&scene));
	if (!(scene->m_mesh = m_mesh_construct()))
		return (scene_destruct(&scene));
	if (!(scene->m_shader = m_shader_construct()))
		return (scene_destruct(&scene));
	return (scene);
}

void		*scene_destruct(t_scene **scene)
{
	if (scene && *scene)
	{
		if ((*scene)->m_mesh)
			m_mesh_destruct(&(*scene)->m_mesh);
		if ((*scene)->m_model)
			m_model_destruct(&(*scene)->m_model);
		if ((*scene)->m_shader)
			m_shader_destruct(&(*scene)->m_shader);
		ft_memdel((void **)scene);
	}
	return (NULL);
}
