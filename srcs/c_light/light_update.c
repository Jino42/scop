#include "scop.h"

void		light_compute_transform(t_light *light, t_model *model)
{
	t_vector	scaling;
	float		same_scaling;

	light->update = false;
	matrix_identity(&light->transform);
	if (light->flag & MODEL_SAME_SCALING)
	{
		same_scaling = model->inter_scaling * model->same_scaling;
		matrix_scaling(&light->transform, same_scaling);
	}
	else
	{
		scaling = vector_get_mult(&model->scaling, model->inter_scaling);
		matrix_vector_scaling(&light->transform, &scaling);
	}
	light->direction = vector_construct(0, 1, 0);
	light->direction = vector_get_rotate(&light->direction, &light->rotation);
	matrixgl_rotation_x(&light->transform, light->rotation.x);
	matrixgl_rotation_y(&light->transform, light->rotation.y);
	matrixgl_rotation_z(&light->transform, light->rotation.z);
	matrixgl_translation(&light->transform, &light->position);
}
