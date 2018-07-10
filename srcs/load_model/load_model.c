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
			int ret = 0;
			if (lm->mesh->flag == SCOP_V)
			{
				ret = sscanf(lm->line, "%s %i %i %i %i\n", lm->type, &lm->buffer_index_v[0], &lm->buffer_index_v[1], &lm->buffer_index_v[2], &lm->buffer_index_v[3]);
				if (ret != 4)
					return (false);
				ret = (ret - 1);
			}
			if (lm->mesh->flag == (SCOP_V | SCOP_VN))
			{
				ret = sscanf(lm->line, "%s %i//%i %i//%i %i//%i %i//%i\n", lm->type,
													&lm->buffer_index_v[0], &lm->buffer_index_vn[0],
													&lm->buffer_index_v[1], &lm->buffer_index_vn[1],
													&lm->buffer_index_v[2], &lm->buffer_index_vn[2],
													&lm->buffer_index_v[3], &lm->buffer_index_vn[3]);
				if (ret != 7 && ret != 9)
					return (false);
				ret = (ret - 1) >> 1;
			}
			if (lm->mesh->flag == (SCOP_V | SCOP_VT))
			{
				ret = sscanf(lm->line, "%s %i/%i %i/%i %i/%i %i/%i\n", lm->type,
													&lm->buffer_index_v[0], &lm->buffer_index_vt[0],
													&lm->buffer_index_v[1], &lm->buffer_index_vt[1],
													&lm->buffer_index_v[2], &lm->buffer_index_vt[2],
													&lm->buffer_index_v[3], &lm->buffer_index_vt[3]);
				if (ret != 7 && ret != 9)
					return (false);
				ret = (ret - 1) >> 1;
			}
			if (lm->mesh->flag == (SCOP_V | SCOP_VN | SCOP_VT))
			{
				ret = sscanf(lm->line, "%s %i/%i/%i %i/%i/%i %i/%i/%i %i/%i/%i\n", lm->type,
													&lm->buffer_index_v[0], &lm->buffer_index_vt[0], &lm->buffer_index_vn[0],
													&lm->buffer_index_v[1], &lm->buffer_index_vt[1], &lm->buffer_index_vn[1],
													&lm->buffer_index_v[2], &lm->buffer_index_vt[2], &lm->buffer_index_vn[2],
													&lm->buffer_index_v[3], &lm->buffer_index_vt[3], &lm->buffer_index_vn[3]);
				if (ret != 10 && ret != 13)
					return (false);
				ret = (ret - 1) >> 2;
			}
			int sommet = 0;
			while (sommet < 3)
			{
				lm->mesh->indices[lm->mesh->nb_indices] = lm->mesh->nb_indices;
				if (lm->mesh->flag & SCOP_V)
				{
					lm->mesh->indexed_v[lm->mesh->nb_indices * 3 + 0] = lm->v[(lm->buffer_index_v[sommet] - 1) * 3 + 0];
					lm->mesh->indexed_v[lm->mesh->nb_indices * 3 + 1] = lm->v[(lm->buffer_index_v[sommet] - 1) * 3 + 1];
					lm->mesh->indexed_v[lm->mesh->nb_indices * 3 + 2] = lm->v[(lm->buffer_index_v[sommet] - 1) * 3 + 2];
				}
				if (lm->mesh->flag & SCOP_VT)
				{
					lm->mesh->indexed_vt[lm->mesh->nb_indices * 2 + 0] = lm->vt[(lm->buffer_index_vt[sommet] - 1) * 2 + 0];
					lm->mesh->indexed_vt[lm->mesh->nb_indices * 2 + 1] = lm->vt[(lm->buffer_index_vt[sommet] - 1) * 2 + 1];
				}
				if (lm->mesh->flag & SCOP_VN)
				{
					lm->mesh->indexed_vn[lm->mesh->nb_indices * 3 + 0] = lm->vn[(lm->buffer_index_vn[sommet] - 1) * 3 + 0];
					lm->mesh->indexed_vn[lm->mesh->nb_indices * 3 + 1] = lm->vn[(lm->buffer_index_vn[sommet] - 1) * 3 + 1];
					lm->mesh->indexed_vn[lm->mesh->nb_indices * 3 + 2] = lm->vn[(lm->buffer_index_vn[sommet] - 1) * 3 + 2];
				}
				lm->mesh->nb_indices++;
				sommet++;
			}
			lm->mesh->nb_faces++;
			if (ret == 4)
			{
				sommet = 0;
				while (sommet < 4)
				{
					if (sommet == 1)
						sommet++;
					lm->mesh->indices[lm->mesh->nb_indices] = lm->mesh->nb_indices;
					if (lm->mesh->flag & SCOP_V)
					{
						lm->mesh->indexed_v[lm->mesh->nb_indices * 3 + 0] = lm->v[(lm->buffer_index_v[sommet] - 1) * 3 + 0];
						lm->mesh->indexed_v[lm->mesh->nb_indices * 3 + 1] = lm->v[(lm->buffer_index_v[sommet] - 1) * 3 + 1];
						lm->mesh->indexed_v[lm->mesh->nb_indices * 3 + 2] = lm->v[(lm->buffer_index_v[sommet] - 1) * 3 + 2];
					}
					if (lm->mesh->flag & SCOP_VT)
					{
						lm->mesh->indexed_vt[lm->mesh->nb_indices * 2 + 0] = lm->vt[(lm->buffer_index_vt[sommet] - 1) * 2 + 0];
						lm->mesh->indexed_vt[lm->mesh->nb_indices * 2 + 1] = lm->vt[(lm->buffer_index_vt[sommet] - 1) * 2 + 1];
					}
					if (lm->mesh->flag & SCOP_VN)
					{
						lm->mesh->indexed_vn[lm->mesh->nb_indices * 3 + 0] = lm->vn[(lm->buffer_index_vn[sommet] - 1) * 3 + 0];
						lm->mesh->indexed_vn[lm->mesh->nb_indices * 3 + 1] = lm->vn[(lm->buffer_index_vn[sommet] - 1) * 3 + 1];
						lm->mesh->indexed_vn[lm->mesh->nb_indices * 3 + 2] = lm->vn[(lm->buffer_index_vn[sommet] - 1) * 3 + 2];
					}
					lm->mesh->nb_indices++;
					sommet++;
				}
				lm->mesh->nb_faces++;
			}
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

	// LE FAIRE SUR TOUS*************
	model_gen_gl_buffers(model);

	for (size_t i = 0; i < lm->model->m_mesh->size; i++) {
		printf("%i\n", lm->model->m_mesh->mesh[i]->VBO);
	}

	model_setup_scaling(model);
	scene->model_add(scene, model);
	//obj_pars_debug(lm->mesh);
	//if (tex)
	//	lm->mesh->flag |= F_TEXTURE;
	return (true);
}
