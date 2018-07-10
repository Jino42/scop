#include "scop.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void mesh_buffers(t_mesh *mesh, const uint32_t flag)
{
	glGenBuffers(1, &mesh->EBO);
	glGenVertexArrays(1, &mesh->VAO);

	glBindVertexArray(mesh->VAO);

	if (flag & SCOP_V)
	{
		ft_printf("Set buffer : V\n");
		glGenBuffers(1, &mesh->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (mesh->nb_indices) * 3, mesh->indexed_v, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	if (flag & SCOP_VN)
	{
		ft_printf("Set buffer : VN\n");
		glGenBuffers(1, &mesh->VNBO);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->VNBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (mesh->nb_indices) * 3, mesh->indexed_vn, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	if (flag & SCOP_VT)
	{
		ft_printf("Set buffer : VT\n");
		glGenBuffers(1, &mesh->VTBO);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->VTBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (mesh->nb_indices) * 2, mesh->indexed_vt, GL_STATIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh->nb_indices, mesh->indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

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
	int j = 0;

	t_lm *lm = lm_construct(path_obj);
	t_mesh *mesh = lm->mesh;
	t_model *model = lm->model;
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
			if (mesh->flag == SCOP_V)
			{
				ret = sscanf(lm->line, "%s %i %i %i %i\n", lm->type, &lm->buffer_index_v[0], &lm->buffer_index_v[1], &lm->buffer_index_v[2], &lm->buffer_index_v[3]);
				if (ret != 4)
					return (false);
				ret = (ret - 1);
			}
			if (mesh->flag == (SCOP_V | SCOP_VN))
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
			if (mesh->flag == (SCOP_V | SCOP_VT))
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
			if (mesh->flag == (SCOP_V | SCOP_VN | SCOP_VT))
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
				mesh->indices[j] = j;
				if (mesh->flag & SCOP_V)
				{
					mesh->indexed_v[j * 3 + 0] = lm->v[(lm->buffer_index_v[sommet] - 1) * 3 + 0];
					mesh->indexed_v[j * 3 + 1] = lm->v[(lm->buffer_index_v[sommet] - 1) * 3 + 1];
					mesh->indexed_v[j * 3 + 2] = lm->v[(lm->buffer_index_v[sommet] - 1) * 3 + 2];
					mesh->nb_indexed_v++;
				}
				if (mesh->flag & SCOP_VT)
				{
					mesh->indexed_vt[j * 2 + 0] = lm->vt[(lm->buffer_index_vt[sommet] - 1) * 2 + 0];
					mesh->indexed_vt[j * 2 + 1] = lm->vt[(lm->buffer_index_vt[sommet] - 1) * 2 + 1];
					mesh->nb_indexed_vt++;
				}
				if (mesh->flag & SCOP_VN)
				{
					mesh->indexed_vn[j * 3 + 0] = lm->vn[(lm->buffer_index_vn[sommet] - 1) * 3 + 0];
					mesh->indexed_vn[j * 3 + 1] = lm->vn[(lm->buffer_index_vn[sommet] - 1) * 3 + 1];
					mesh->indexed_vn[j * 3 + 2] = lm->vn[(lm->buffer_index_vn[sommet] - 1) * 3 + 2];
					mesh->nb_indexed_vn++;
				}
				j++;
				sommet++;
			}
			mesh->nb_indices += 3;
			mesh->nb_faces += 1;
			if (ret == 4)
			{
				sommet = 0;
				while (sommet < 4)
				{
					if (sommet == 1)
						sommet++;
					mesh->indices[j] = j;
					if (mesh->flag & SCOP_V)
					{
						mesh->indexed_v[j * 3 + 0] = lm->v[(lm->buffer_index_v[sommet] - 1) * 3 + 0];
						mesh->indexed_v[j * 3 + 1] = lm->v[(lm->buffer_index_v[sommet] - 1) * 3 + 1];
						mesh->indexed_v[j * 3 + 2] = lm->v[(lm->buffer_index_v[sommet] - 1) * 3 + 2];
						mesh->nb_indexed_v++;
					}
					if (mesh->flag & SCOP_VT)
					{
						mesh->indexed_vt[j * 2 + 0] = lm->vt[(lm->buffer_index_vt[sommet] - 1) * 2 + 0];
						mesh->indexed_vt[j * 2 + 1] = lm->vt[(lm->buffer_index_vt[sommet] - 1) * 2 + 1];
						mesh->nb_indexed_vt++;
					}
					if (mesh->flag & SCOP_VN)
					{
						mesh->indexed_vn[j * 3 + 0] = lm->vn[(lm->buffer_index_vn[sommet] - 1) * 3 + 0];
						mesh->indexed_vn[j * 3 + 1] = lm->vn[(lm->buffer_index_vn[sommet] - 1) * 3 + 1];
						mesh->indexed_vn[j * 3 + 2] = lm->vn[(lm->buffer_index_vn[sommet] - 1) * 3 + 2];
						mesh->nb_indexed_vn++;
					}
					j++;
					sommet++;
				}
				mesh->nb_indices += 3;
				mesh->nb_faces += 1;
			}
		}
		else if(!strcmp("mtllib", lm->type))
		{
		}
		else if (!strcmp("usemtl", lm->type))
		{
		}
		else if (!strcmp("o", lm->type) && mesh->nb_indices)
		{
		}
		ft_strdel(&lm->line);
		if (j * sizeof(GLuint) >= lm->mem_len_indices)
		{
			lm->mem_len_indices += BUFFER_OBJ * sizeof(GLuint);
			mesh->indices = realloc(mesh->indices, lm->mem_len_indices);
		}
		if ((mesh->nb_indexed_v) * sizeof(GLfloat) * 3 >= lm->mem_len_indexed_v)
		{
			lm->mem_len_indexed_v += BUFFER_OBJ * sizeof(GLfloat);
			mesh->indexed_v = realloc(mesh->indexed_v, lm->mem_len_indexed_v);
		}
		if ((mesh->nb_indexed_vn) * sizeof(GLfloat) * 3 >= lm->mem_len_indexed_vn)
		{
			lm->mem_len_indexed_vn += BUFFER_OBJ * sizeof(GLfloat);
			mesh->indexed_vn = realloc(mesh->indexed_vn, lm->mem_len_indexed_vn);
		}
		if ((mesh->nb_indexed_vt) * sizeof(GLfloat) * 2 >= lm->mem_len_indexed_vt)
		{
			lm->mem_len_indexed_vt += BUFFER_OBJ * sizeof(GLfloat);
			mesh->indexed_vt = realloc(mesh->indexed_vt, lm->mem_len_indexed_vt);
		}
		if ((lm->nb_v) * sizeof(GLfloat) * 3 >= lm->mem_len_v)
		{
			lm->mem_len_v += BUFFER_OBJ * sizeof(GLfloat);
			lm->v = realloc(lm->v, lm->mem_len_v);
		}
		if ((lm->nb_vt) * sizeof(GLfloat) * 2 >= lm->mem_len_vt)
		{
			lm->mem_len_vt += BUFFER_OBJ * sizeof(GLfloat);
			lm->vt = realloc(lm->vt, lm->mem_len_vt);
		}
		if ((lm->nb_vn) * sizeof(GLfloat) * 3 >= lm->mem_len_vn)
		{
			lm->mem_len_vn += BUFFER_OBJ * sizeof(GLfloat);
			lm->vn = realloc(lm->vn, lm->mem_len_vn);
		}
	}

	// LE FAIRE SUR TOUS*************
	mesh_buffers(mesh, mesh->flag);
	model_setup_scaling(model);
	scene->mesh_add(scene, mesh);
	scene->model_add(scene, model);
	//obj_pars_debug(mesh);
	//if (tex)
	//	mesh->flag |= F_TEXTURE;
	return (true);
}
