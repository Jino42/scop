#include "scop.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

bool	obj_pars_debug(t_lm *lm)
{
	int index;
	int fd;

	fd = open("debug", O_RDWR | O_TRUNC | S_IRWXU);
	index = 0;
	dprintf(fd, "v: %i\n", lm->nb_v);
	printf("%i\n", lm->nb_v);
	while (index < lm->nb_v)
	{
		dprintf(fd, "v %f %f %f\n", lm->v[3 * index + 0],
										lm->v[3 * index + 1],
										lm->v[3 * index + 2]);
		index++;
	}
	close(fd);
	return (true);
}

void	model_setup_scaling(t_model *model)
{
	t_vector	diff;
	float		scaling;

	diff = vector_get_sub(&model->min, &model->max);
	diff = vector_get_abs(&diff);
	if (diff.x > diff.y && diff.x > diff.z)
		scaling = 1.f / diff.x;
	else if (diff.y > diff.x && diff.y > diff.z)
		scaling = 1.f / diff.y;
	else
		scaling = 1.f / diff.z;
	matrix_scaling(&model->transform, scaling);
	diff = vector_construct(0.f, -0.5f, 0.f);
	matrixgl_translation(&model->transform, &diff);
	model->center = diff;
	model->negative_center = vector_get_invert(&diff);
}

bool	obj_pars(t_scene *scene, const char * path_obj)
{
	t_model *model = model_construct();
	t_lm *lm = lm_construct(model, path_obj);
	while (get_next_line(lm->fd, &lm->line) == 1)
	{
		sscanf(lm->line, "%s ", lm->type);
		if (!strcmp("#", lm->type))
			;
		else if (!strcmp("vn", lm->type))
			lm_get_vnormal(lm);
		else if (!strcmp("vt", lm->type))
			lm_get_vtexel(lm);
		else if (!strcmp("v", lm->type))
			lm_get_vertex(lm);
		else if (!strcmp("f", lm->type))
		{
			if (!lm_get_face(lm))
				return (false);
		}
		else if(!strcmp("mtllib", lm->type))
		{
		}
		else if (!strcmp("usemtl", lm->type))
		{
		}
		else if (!strcmp("o", lm->type) && lm->mesh->nb_indices)
			lm_add_mesh(lm);
		ft_strdel(&lm->line);
		lm_check_realloc(lm);
	}
	model_gen_gl_buffers(model);
	model_setup_scaling(model);
	scene->model_add(scene, model);
	return (true);
}
