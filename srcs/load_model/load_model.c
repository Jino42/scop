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
		/*for(int32_t i = 0;i< (int32_t)mesh->nb_indices;i++)
		{
			printf("%.2f %.2f\n", mesh->indexed_vt[i*2], mesh->indexed_vt[i*2+1]);
		}*/
	}


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh->nb_indices, mesh->indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

bool	obj_pars_debug(t_mesh *mesh)
{
	int index;
	int fd;

	fd = open("debug", O_RDWR | O_TRUNC | S_IRWXU);
	index = 0;
	dprintf(fd, "v: %i\n", mesh->nb_v);
	printf("%i\n", mesh->nb_v);
	while (index < mesh->nb_v)
	{
		dprintf(fd, "v %f %f %f\n", mesh->v[3 * index + 0],
										mesh->v[3 * index + 1],
										mesh->v[3 * index + 2]);
		index++;
	}
	close(fd);
	return (true);
}

void	model_min_max_vertex(t_model *model, float v[4])
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
	printf("Scaling %f", scaling);
	matrix_scaling(&model->transform, scaling);
	diff = vector_construct(0.f, -0.5f, 0.f);
	matrixgl_translation(&model->transform, &diff);
}

bool	obj_pars(t_scene *scene, const char * path_obj)
{
	int			fd;
	char		*line;
	char		type[10];
	//char		name[1024];
	int			index_v[4];
	int			index_vt[4];
	int			index_vn[4];
	float		v[4];
	float		vt[4];
	float		vn[4];
	t_mesh		*mesh;
	t_model		*model;
	//bool		tex = false;

	fd = open(path_obj, O_RDONLY);
	if (!fd || fd < 0)
		return (false);


	line = NULL;
	uint32_t mem_len_indices = BUFFER_OBJ * sizeof(GLuint); (void)mem_len_indices;
	uint32_t mem_len_indexed_v = BUFFER_OBJ * sizeof(GLfloat); (void)mem_len_indexed_v;
	uint32_t mem_len_indexed_vn = BUFFER_OBJ * sizeof(GLfloat); (void)mem_len_indexed_vn;
	uint32_t mem_len_indexed_vt = BUFFER_OBJ * sizeof(GLfloat); (void)mem_len_indexed_vt;
	uint32_t mem_len_v = BUFFER_OBJ * sizeof(GLfloat); (void)mem_len_v;
	uint32_t mem_len_vt = BUFFER_OBJ * sizeof(GLfloat); (void)mem_len_vt;
	uint32_t mem_len_vn = BUFFER_OBJ * sizeof(GLfloat); (void)mem_len_vn;
	uint32_t last_index_v;
	uint32_t last_index_vt;
	uint32_t last_index_vn;
	uint32_t last_index;

	last_index_v = 0;
	last_index_vt = 0;
	last_index_vn = 0;
	last_index = 0;
	int j = 0;
	if (!(mesh = mesh_construct()))
		return (false);
	if (!(model = model_construct()))
		return (false);
	while (get_next_line(fd, &line) == 1)
	{
		sscanf(line, "%s ", type);
		if (!strcmp("#", type))
			;
		else if (!strcmp("vn", type))
		{
			mesh->flag |= SCOP_VN;
			if (sscanf(line, "%s %f %f %f\n", type, &v[0], &v[1], &v[2]) != 4)
				return (false);
			mesh->vn[3 * mesh->nb_vn + 0] = v[0];
			mesh->vn[3 * mesh->nb_vn + 1] = v[1];
			mesh->vn[3 * mesh->nb_vn + 2] = v[2];
			mesh->nb_vn++;
		}
		else if (!strcmp("vt", type))
		{
			mesh->flag |= SCOP_VT;
			if (sscanf(line, "%s %f %f\n", type, &vt[0], &vt[1]) != 3)
				return (false);
			mesh->vt[2 * mesh->nb_vt + 0] = vt[0];
			mesh->vt[2 * mesh->nb_vt + 1] = vt[1];
			mesh->nb_vt++;
		}
		else if (!strcmp("v", type))
		{
			mesh->flag |= SCOP_V;
			if (sscanf(line, "%s %f %f %f\n", type, &vn[0], &vn[1], &vn[2]) != 4)
				return (false);
			mesh->v[3 * mesh->nb_v + 0] = vn[0];
			mesh->v[3 * mesh->nb_v + 1] = vn[1];
			mesh->v[3 * mesh->nb_v + 2] = vn[2];
			mesh->nb_v++;
			model_min_max_vertex(model, vn);
		}
		else if (!strcmp("f", type))
		{
			int ret = 0;
			if (mesh->flag == SCOP_V)
			{
				ret = sscanf(line, "%s %i %i %i %i\n", type, &index_v[0], &index_v[1], &index_v[2], &index_v[3]);
				if (ret != 4)
					return (false);
				ret = (ret - 1);
			}
			if (mesh->flag == (SCOP_V | SCOP_VN))
			{
				ret = sscanf(line, "%s %i//%i %i//%i %i//%i %i//%i\n", type,
													&index_v[0], &index_vn[0],
													&index_v[1], &index_vn[1],
													&index_v[2], &index_vn[2],
													&index_v[3], &index_vn[3]);
				if (ret != 7 && ret != 9)
					return (false);
				ret = (ret - 1) >> 1;
			}
			if (mesh->flag == (SCOP_V | SCOP_VT))
			{
				ret = sscanf(line, "%s %i/%i %i/%i %i/%i %i/%i\n", type,
													&index_v[0], &index_vt[0],
													&index_v[1], &index_vt[1],
													&index_v[2], &index_vt[2],
													&index_v[3], &index_vt[3]);
				if (ret != 7 && ret != 9)
					return (false);
				ret = (ret - 1) >> 1;
			}
			if (mesh->flag == (SCOP_V | SCOP_VN | SCOP_VT))
			{
				ret = sscanf(line, "%s %i/%i/%i %i/%i/%i %i/%i/%i %i/%i/%i\n", type,
													&index_v[0], &index_vt[0], &index_vn[0],
													&index_v[1], &index_vt[1], &index_vn[1],
													&index_v[2], &index_vt[2], &index_vn[2],
													&index_v[3], &index_vt[3], &index_vn[3]);
				if (ret != 10 && ret != 13)
					return (false);
				ret = (ret - 1) >> 2;
			}
			int sommet = 0;
			while (sommet < 3)
			{
				mesh->indices[j - last_index] = j - last_index;
				if (mesh->flag & SCOP_V)
				{
					mesh->indexed_v[(j - last_index) * 3 + 0] = mesh->v[(index_v[sommet] - 1 - last_index_v) * 3 + 0];
					mesh->indexed_v[(j - last_index) * 3 + 1] = mesh->v[(index_v[sommet] - 1 - last_index_v) * 3 + 1];
					mesh->indexed_v[(j - last_index) * 3 + 2] = mesh->v[(index_v[sommet] - 1 - last_index_v) * 3 + 2];
					mesh->nb_indexed_v++;
				}
				if (mesh->flag & SCOP_VT)
				{
					mesh->indexed_vt[(j - last_index) * 2 + 0] = mesh->vt[(index_vt[sommet] - 1 - last_index_vt) * 2 + 0];
					mesh->indexed_vt[(j - last_index) * 2 + 1] = mesh->vt[(index_vt[sommet] - 1 - last_index_vt) * 2 + 1];
					mesh->nb_indexed_vt++;
				}
				if (mesh->flag & SCOP_VN)
				{
					mesh->indexed_vn[(j - last_index) * 3 + 0] = mesh->vn[(index_vn[sommet] - 1 - last_index_vn) * 3 + 0];
					mesh->indexed_vn[(j - last_index) * 3 + 1] = mesh->vn[(index_vn[sommet] - 1 - last_index_vn) * 3 + 1];
					mesh->indexed_vn[(j - last_index) * 3 + 2] = mesh->vn[(index_vn[sommet] - 1 - last_index_vn) * 3 + 2];
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
					mesh->indices[j - last_index] = j - last_index;
					if (mesh->flag & SCOP_V)
					{
						mesh->indexed_v[(j - last_index) * 3 + 0] = mesh->v[(index_v[sommet] - 1 - last_index_v) * 3 + 0];
						mesh->indexed_v[(j - last_index) * 3 + 1] = mesh->v[(index_v[sommet] - 1 - last_index_v) * 3 + 1];
						mesh->indexed_v[(j - last_index) * 3 + 2] = mesh->v[(index_v[sommet] - 1 - last_index_v) * 3 + 2];
						mesh->nb_indexed_v++;
					}
					if (mesh->flag & SCOP_VT)
					{
						mesh->indexed_vt[(j - last_index) * 2 + 0] = mesh->vt[(index_vt[sommet] - 1 - last_index_vt) * 2 + 0];
						mesh->indexed_vt[(j - last_index) * 2 + 1] = mesh->vt[(index_vt[sommet] - 1 - last_index_vt) * 2 + 1];
						mesh->nb_indexed_vt++;
					}
					if (mesh->flag & SCOP_VN)
					{
						mesh->indexed_vn[(j - last_index) * 3 + 0] = mesh->vn[(index_vn[sommet] - 1 - last_index_vn) * 3 + 0];
						mesh->indexed_vn[(j - last_index) * 3 + 1] = mesh->vn[(index_vn[sommet] - 1 - last_index_vn) * 3 + 1];
						mesh->indexed_vn[(j - last_index) * 3 + 2] = mesh->vn[(index_vn[sommet] - 1 - last_index_vn) * 3 + 2];
						mesh->nb_indexed_vn++;
					}
					j++;
					sommet++;
				}
				mesh->nb_indices += 3;
				mesh->nb_faces += 1;
			}
		}
		else if(!strcmp("mtllib", type))
		{
		}
		else if (!strcmp("usemtl", type))
		{
		}
		else if (!strcmp("o", type) && mesh->nb_indices)
		{
		}
		ft_strdel(&line);
		if ((j - last_index + 19) * sizeof(GLuint) >= mem_len_indices)
		{
			mem_len_indices += BUFFER_OBJ * sizeof(GLuint);
			mesh->indices = realloc(mesh->indices, mem_len_indices);
		}
		if ((mesh->nb_indexed_v + 19) * sizeof(GLfloat) * 3 >= mem_len_indexed_v)
		{
			mem_len_indexed_v += BUFFER_OBJ * sizeof(GLfloat);
			mesh->indexed_v = realloc(mesh->indexed_v, mem_len_indexed_v);
		}
		if ((mesh->nb_indexed_vn + 19) * sizeof(GLfloat) * 3 >= mem_len_indexed_vn)
		{
			mem_len_indexed_vn += BUFFER_OBJ * sizeof(GLfloat);
			mesh->indexed_vn = realloc(mesh->indexed_vn, mem_len_indexed_vn);
		}
		if ((mesh->nb_indexed_vt + 19) * sizeof(GLfloat) * 2 >= mem_len_indexed_vt)
		{
			mem_len_indexed_vt += BUFFER_OBJ * sizeof(GLfloat);
			mesh->indexed_vt = realloc(mesh->indexed_vt, mem_len_indexed_vt);
		}
		if ((mesh->nb_v + 19) * sizeof(GLfloat) * 3 >= mem_len_v)
		{
			mem_len_v += BUFFER_OBJ * sizeof(GLfloat);
			mesh->v = realloc(mesh->v, mem_len_v);
		}
		if ((mesh->nb_vt + 19) * sizeof(GLfloat) * 2 >= mem_len_vt)
		{
			mem_len_vt += BUFFER_OBJ * sizeof(GLfloat);
			mesh->vt = realloc(mesh->vt, mem_len_vt);
		}
		if ((mesh->nb_vn + 19) * sizeof(GLfloat) * 3 >= mem_len_vn)
		{
			mem_len_vn += BUFFER_OBJ * sizeof(GLfloat);
			mesh->vn = realloc(mesh->vn, mem_len_vn);
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
