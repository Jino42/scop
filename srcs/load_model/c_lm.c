#include "scop.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

t_lm		*lm_construct(t_scene *scene, t_model *model, const char *path_obj)
{
	t_lm	*lm;
	int		fd;

	fd = open(path_obj, O_RDONLY);
	if (!fd || fd < 0)
		return (NULL);
	if (!(lm = ft_memalloc(sizeof(t_lm))))
		return (NULL);
	lm->model = model;
	lm->scene = scene;
	if (!(lm->mesh = lm->model->m_mesh->new(lm->model->m_mesh)))
		return (lm_destruct(&lm));
	if (!(lm->v = ft_memalloc(sizeof(GLfloat) * BUFFER_OBJ)))
		return (lm_destruct(&lm));
	if (!(lm->vt = ft_memalloc(sizeof(GLfloat) * BUFFER_OBJ)))
		return (lm_destruct(&lm));
	if (!(lm->vn = ft_memalloc(sizeof(GLfloat) * BUFFER_OBJ)))
		return (lm_destruct(&lm));
	lm->mem_len_indices = BUFFER_OBJ * sizeof(GLuint);
	lm->mem_len_indexed_v = BUFFER_OBJ * sizeof(GLfloat);
	lm->mem_len_indexed_vn = BUFFER_OBJ * sizeof(GLfloat);
	lm->mem_len_indexed_vt = BUFFER_OBJ * sizeof(GLfloat);
	lm->mem_len_v = BUFFER_OBJ * sizeof(GLfloat);
	lm->mem_len_vt = BUFFER_OBJ * sizeof(GLfloat);
	lm->mem_len_vn = BUFFER_OBJ * sizeof(GLfloat);
	lm->fd = fd;
	return (lm);
}

void		*lm_destruct(t_lm **c_lm)
{
	t_lm	*lm;

	if (c_lm && *c_lm)
	{
		lm = *c_lm;
		ft_memdel((void **)&lm->v);
		ft_memdel((void **)&lm->vt);
		ft_memdel((void **)&lm->vn);
		ft_memdel((void **)c_lm);
	}
	return (NULL);
}

bool		lm_add_mesh(t_lm *lm)
{
	if (!(lm->mesh = lm->model->m_mesh->new(lm->model->m_mesh)))
		return (lm_destruct(&lm));
	lm->mem_len_indices = BUFFER_OBJ * sizeof(GLuint);
	lm->mem_len_indexed_v = BUFFER_OBJ * sizeof(GLfloat);
	lm->mem_len_indexed_vn = BUFFER_OBJ * sizeof(GLfloat);
	lm->mem_len_indexed_vt = BUFFER_OBJ * sizeof(GLfloat);
	/*
	lm->mem_len_v = BUFFER_OBJ * sizeof(GLfloat);
	lm->mem_len_vt = BUFFER_OBJ * sizeof(GLfloat);
	lm->mem_len_vn = BUFFER_OBJ * sizeof(GLfloat);
	ft_memdel((void **)&lm->v);
	ft_memdel((void **)&lm->vt);
	ft_memdel((void **)&lm->vn);
	if (!(lm->v = ft_memalloc(sizeof(GLfloat) * BUFFER_OBJ)))
		return (lm_destruct(&lm));
	if (!(lm->vt = ft_memalloc(sizeof(GLfloat) * BUFFER_OBJ)))
		return (lm_destruct(&lm));
	if (!(lm->vn = ft_memalloc(sizeof(GLfloat) * BUFFER_OBJ)))
		return (lm_destruct(&lm));
	*/
	return (true);
}

void	lm_min_max_vertex(t_model *model, float v[4])
{
	if (v[0] > model->max.x)
		model->max.x = v[0];
	else if (v[0] < model->min.x)
		model->min.x = v[0];
	else if (v[1] > model->max.y)
		model->max.y = v[1];
	else if (v[1] < model->min.y)
		model->min.y = v[1];
	else if (v[2] > model->max.z)
		model->max.z = v[2];
	else if (v[2] < model->min.z)
		model->min.z = v[2];
}

bool	lm_check_realloc(t_lm *lm)
{
	t_mesh *mesh;

	mesh = lm->mesh;
	if ((mesh->nb_indices + 18) * sizeof(GLuint) >= lm->mem_len_indices)
	{
		lm->mem_len_indices += BUFFER_OBJ * sizeof(GLuint);
		if (!(mesh->indices = realloc(mesh->indices, lm->mem_len_indices)))
			return (false);
	}
	if ((mesh->nb_indices + 6) * sizeof(GLfloat) * 3 >= lm->mem_len_indexed_v)
	{
		lm->mem_len_indexed_v += BUFFER_OBJ * sizeof(GLfloat);
		if (!(mesh->indexed_v = realloc(mesh->indexed_v, lm->mem_len_indexed_v)))
			return (false);
	}
	if ((mesh->nb_indices + 6) * sizeof(GLfloat) * 2 >= lm->mem_len_indexed_vt)
	{
		lm->mem_len_indexed_vt += BUFFER_OBJ * sizeof(GLfloat);
		if (!(mesh->indexed_vt = realloc(mesh->indexed_vt, lm->mem_len_indexed_vt)))
			return (false);
	}
	if ((mesh->nb_indices + 6) * sizeof(GLfloat) * 3 >= lm->mem_len_indexed_vn)
	{
		lm->mem_len_indexed_vn += BUFFER_OBJ * sizeof(GLfloat);
		if (!(mesh->indexed_vn = realloc(mesh->indexed_vn, lm->mem_len_indexed_vn)))
			return (false);
	}
	if ((lm->nb_v + 6) * sizeof(GLfloat) * 3 >= lm->mem_len_v)
	{
		lm->mem_len_v += BUFFER_OBJ * sizeof(GLfloat);
		if (!(lm->v = realloc(lm->v, lm->mem_len_v)))
			return (false);
	}
	if ((lm->nb_vt + 6) * sizeof(GLfloat) * 2 >= lm->mem_len_vt)
	{
		lm->mem_len_vt += BUFFER_OBJ * sizeof(GLfloat);
		if (!(lm->vt = realloc(lm->vt, lm->mem_len_vt)))
			return (false);
	}
	if ((lm->nb_vn + 6) * sizeof(GLfloat) * 3 >= lm->mem_len_vn)
	{
		lm->mem_len_vn += BUFFER_OBJ * sizeof(GLfloat);
		if (!(lm->vn = realloc(lm->vn, lm->mem_len_vn)))
			return (false);
	}
	return (true);
}

bool	lm_get_vtexel(t_lm *lm)
{
	t_mesh *mesh;

	mesh = lm->mesh;
	mesh->flag |= SCOP_VT;
	if (sscanf(lm->line, "%s %f %f\n", lm->type, &lm->buffer_vt[0], &lm->buffer_vt[1]) != 3)
		return (false);
	lm->vt[2 * lm->nb_vt + 0] = lm->buffer_vt[0];
	lm->vt[2 * lm->nb_vt + 1] = lm->buffer_vt[1];
	lm->nb_vt++;
	return (true);
}

bool	lm_get_vnormal(t_lm *lm)
{
	t_mesh *mesh;

	mesh = lm->mesh;
	mesh->flag |= SCOP_VN;
	if (sscanf(lm->line, "%s %f %f %f\n", lm->type, &lm->buffer_vn[0], &lm->buffer_vn[1], &lm->buffer_vn[2]) != 4)
		return (false);
	lm->vn[3 * lm->nb_vn + 0] = lm->buffer_vn[0];
	lm->vn[3 * lm->nb_vn + 1] = lm->buffer_vn[1];
	lm->vn[3 * lm->nb_vn + 2] = lm->buffer_vn[2];
	lm->nb_vn++;
	return (true);
}

bool	lm_get_vertex(t_lm *lm)
{
	t_mesh *mesh;

	mesh = lm->mesh;
	mesh->flag |= SCOP_V;
	if (sscanf(lm->line, "%s %f %f %f\n", lm->type, &lm->buffer_v[0], &lm->buffer_v[1], &lm->buffer_v[2]) != 4)
		return (false);
	lm->v[3 * lm->nb_v + 0] = lm->buffer_v[0];
	lm->v[3 * lm->nb_v + 1] = lm->buffer_v[1];
	lm->v[3 * lm->nb_v + 2] = lm->buffer_v[2];
	lm->nb_v++;
	lm_min_max_vertex(lm->model, lm->buffer_v);
	return (true);
}

static int	lm_get_face_v(t_lm *lm)
{
	int ret = 0;

	ret = sscanf(lm->line, "%s %i %i %i %i\n", lm->type, &lm->buffer_index_v[0], &lm->buffer_index_v[1], &lm->buffer_index_v[2], &lm->buffer_index_v[3]);
	if (ret != 4)
		return (0);
	return (ret - 1);
}
static int	lm_get_face_v_vn(t_lm *lm)
{
	int ret;

	ret = sscanf(lm->line, "%s %i//%i %i//%i %i//%i %i//%i\n", lm->type,
							&lm->buffer_index_v[0], &lm->buffer_index_vn[0],
							&lm->buffer_index_v[1], &lm->buffer_index_vn[1],
							&lm->buffer_index_v[2], &lm->buffer_index_vn[2],
							&lm->buffer_index_v[3], &lm->buffer_index_vn[3]);
	if (ret != 7 && ret != 9)
		return (0);
	return (ret - 1) >> 1;
}
static int	lm_get_face_v_vt(t_lm *lm)
{
	int ret;

	ret = sscanf(lm->line, "%s %i/%i %i/%i %i/%i %i/%i\n", lm->type,
							&lm->buffer_index_v[0], &lm->buffer_index_vt[0],
							&lm->buffer_index_v[1], &lm->buffer_index_vt[1],
							&lm->buffer_index_v[2], &lm->buffer_index_vt[2],
							&lm->buffer_index_v[3], &lm->buffer_index_vt[3]);
	if (ret != 7 && ret != 9)
		return (0);
	return(ret - 1) >> 1;
}
static int	lm_get_face_v_vn_vt(t_lm *lm)
{
	int ret;

	ret = sscanf(lm->line, "%s %i/%i/%i %i/%i/%i %i/%i/%i %i/%i/%i\n", lm->type,
	&lm->buffer_index_v[0], &lm->buffer_index_vt[0], &lm->buffer_index_vn[0],
	&lm->buffer_index_v[1], &lm->buffer_index_vt[1], &lm->buffer_index_vn[1],
	&lm->buffer_index_v[2], &lm->buffer_index_vt[2], &lm->buffer_index_vn[2],
	&lm->buffer_index_v[3], &lm->buffer_index_vt[3], &lm->buffer_index_vn[3]);
	if (ret != 10 && ret != 13)
		return (0);
	if (ret == 10)
		return (3);
	return (4);
}

static int	lm_get_index_face(t_lm *lm)
{
	if (lm->mesh->flag == SCOP_V)
		return (lm_get_face_v(lm));
	if (lm->mesh->flag == (SCOP_V | SCOP_VN))
		return (lm_get_face_v_vn(lm));
	if (lm->mesh->flag == (SCOP_V | SCOP_VT))
		return (lm_get_face_v_vt(lm));
	if (lm->mesh->flag == (SCOP_V | SCOP_VN | SCOP_VT))
		return (lm_get_face_v_vn_vt(lm));
	return (0);
}

static void	lm_indexing(t_lm *lm, const int sommet)
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
}

static bool	lm_indexing_face(t_lm *lm, const int sommet4)
{
	int sommet = 0;
	while (sommet < 3)
	{
		lm_indexing(lm, sommet);
		sommet++;
	}
	lm->mesh->nb_faces++;

	if (sommet4 == 4)
	{
		sommet = 0;
		while (sommet < 4)
		{
			if (sommet == 1)
				sommet++;
			lm_indexing(lm, sommet);
			sommet++;
		}
		lm->mesh->nb_faces++;
	}
	return (true);
}

bool		lm_get_face(t_lm *lm)
{
	int ret;

	if (!(ret = lm_get_index_face(lm)))
		return (false);
	lm_indexing_face(lm, ret);
	return (true);
}
