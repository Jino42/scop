#include "scop.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

bool	load_model(t_scene *scene, const char *path_obj)
{

	t_model	*model;

	model = model_construct(path_obj);
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
	lm_destruct(&lm);
	return (true);
}
