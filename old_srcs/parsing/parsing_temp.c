/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_temp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 22:45:11 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/07/07 23:26:16 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_mesh	*create_mesh()
{
	t_mesh *mesh;

	if (!(mesh = ft_memalloc(sizeof(t_mesh))))
		return (NULL);
	mesh->v = ft_memalloc(sizeof(GLfloat) * BUFFER_OBJ);
	mesh->vt = ft_memalloc(sizeof(GLfloat) * BUFFER_OBJ);
	mesh->vn = ft_memalloc(sizeof(GLfloat) * BUFFER_OBJ);
	mesh->indexed_v = ft_memalloc(sizeof(GLfloat) * BUFFER_OBJ);
	mesh->indexed_vt = ft_memalloc(sizeof(GLfloat) * BUFFER_OBJ);
	mesh->indexed_vn = ft_memalloc(sizeof(GLfloat) * BUFFER_OBJ);
	mesh->indices = ft_memalloc(sizeof(GLuint) * BUFFER_OBJ);
	return (mesh);
}

bool	obj_pars(t_model *model, const char * path_obj)
{
	int			fd;
	char		*line;
	char		type[10];
	char		name[1024];
	int			index_v[4];
	int			index_vt[4];
	int			index_vn[4];
	float		v[4];
	float		vt[4];
	float		vn[4];
	bool		tex = false;

	fd = open(path_obj, O_RDONLY);
	if (!fd || fd < 0)
		return (false);

	t_mesh *mesh;

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
	if (!model->meshs->size)
	{
		mesh = create_mesh();
		mem_len_indices = BUFFER_OBJ * sizeof(GLuint);
		mem_len_indexed_v = BUFFER_OBJ * sizeof(GLfloat);
		mem_len_indexed_vn = BUFFER_OBJ * sizeof(GLfloat);
		mem_len_indexed_vt = BUFFER_OBJ * sizeof(GLfloat);
		mem_len_v = BUFFER_OBJ * sizeof(GLfloat);
		mem_len_vt = BUFFER_OBJ * sizeof(GLfloat);
		mem_len_vn = BUFFER_OBJ * sizeof(GLfloat);
	}
	while (get_next_line(fd, &line) == 1)
	{
		sscanf(line, "%s ", type);
		if (!strcmp("#", type))
			;
		else if (!strcmp("vn", type))
		{
			model->flag |= SCOP_VN;
			if (sscanf(line, "%s %f %f %f\n", type, &v[0], &v[1], &v[2]) != 4)
				return (false);
			mesh->vn[3 * mesh->nb_vn + 0] = v[0];
			mesh->vn[3 * mesh->nb_vn + 1] = v[1];
			mesh->vn[3 * mesh->nb_vn + 2] = v[2];
			mesh->nb_vn++;
		}
		else if (!strcmp("vt", type))
		{
			model->flag |= SCOP_VT;
			if (sscanf(line, "%s %f %f\n", type, &vt[0], &vt[1]) != 3)
				return (false);
			mesh->vt[2 * mesh->nb_vt + 0] = vt[0];
			mesh->vt[2 * mesh->nb_vt + 1] = vt[1];
			mesh->nb_vt++;
		}
		else if (!strcmp("v", type))
		{
			model->flag |= SCOP_V;
			if (sscanf(line, "%s %f %f %f\n", type, &vn[0], &vn[1], &vn[2]) != 4)
				return (false);
			mesh->v[3 * mesh->nb_v + 0] = vn[0];
			mesh->v[3 * mesh->nb_v + 1] = vn[1];
			mesh->v[3 * mesh->nb_v + 2] = vn[2];
			mesh->nb_v++;
		}
		else if (!strcmp("f", type))
		{
			int ret = 0;
			if (model->flag == SCOP_V)
			{
				ret = sscanf(line, "%s %i %i %i %i\n", type, &index_v[0], &index_v[1], &index_v[2], &index_v[3]);
				if (ret != 4)
					return (false);
				ret = (ret - 1);
			}
			if (model->flag == (SCOP_V | SCOP_VN))
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
			if (model->flag == (SCOP_V | SCOP_VT))
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
			if (model->flag == (SCOP_V | SCOP_VN | SCOP_VT))
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
				if (model->flag & SCOP_V)
				{
					mesh->indexed_v[(j - last_index) * 3 + 0] = mesh->v[(index_v[sommet] - 1 - last_index_v) * 3 + 0];
					mesh->indexed_v[(j - last_index) * 3 + 1] = mesh->v[(index_v[sommet] - 1 - last_index_v) * 3 + 1];
					mesh->indexed_v[(j - last_index) * 3 + 2] = mesh->v[(index_v[sommet] - 1 - last_index_v) * 3 + 2];
					mesh->nb_indexed_v++;
				}
				if (model->flag & SCOP_VT)
				{
					mesh->indexed_vt[(j - last_index) * 2 + 0] = mesh->vt[(index_vt[sommet] - 1 - last_index_vt) * 2 + 0];
					mesh->indexed_vt[(j - last_index) * 2 + 1] = mesh->vt[(index_vt[sommet] - 1 - last_index_vt) * 2 + 1];
					mesh->nb_indexed_vt++;
				}
				if (model->flag & SCOP_VN)
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
					if (model->flag & SCOP_V)
					{
						mesh->indexed_v[(j - last_index) * 3 + 0] = mesh->v[(index_v[sommet] - 1 - last_index_v) * 3 + 0];
						mesh->indexed_v[(j - last_index) * 3 + 1] = mesh->v[(index_v[sommet] - 1 - last_index_v) * 3 + 1];
						mesh->indexed_v[(j - last_index) * 3 + 2] = mesh->v[(index_v[sommet] - 1 - last_index_v) * 3 + 2];
						mesh->nb_indexed_v++;
					}
					if (model->flag & SCOP_VT)
					{
						mesh->indexed_vt[(j - last_index) * 2 + 0] = mesh->vt[(index_vt[sommet] - 1 - last_index_vt) * 2 + 0];
						mesh->indexed_vt[(j - last_index) * 2 + 1] = mesh->vt[(index_vt[sommet] - 1 - last_index_vt) * 2 + 1];
						mesh->nb_indexed_vt++;
					}
					if (model->flag & SCOP_VN)
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
			tex = true;
			sscanf(line, "%s %s\n", type, name);
			char *path_mtl = ft_strjoin((const char *)model->path, name);
			ft_printf("Name mtllib : %s\n", path_mtl);
			if (!parsing_mtl(model, path_mtl))
				exit(0);
		}
		else if (!strcmp("usemtl", type))
		{
			t_material *ptr_material;
			sscanf(line, "%s %s\n", type, name);
			if (!(ptr_material = model->materials->search(model->materials, name)))
			{
				printf("material does not find\n");
				exit(0);
			}
			mesh->material = ptr_material;
		}
		else if (!strcmp("o", type) && mesh->nb_indices)
		{
			ft_printf("Cet object contient des groups\n");
			model->meshs->mesh = realloc((void *)model->meshs->mesh, sizeof(t_mesh **) * (model->meshs->size + 1));
			last_index_v += mesh->nb_v;
			last_index_vn += mesh->nb_vn;
			last_index_vt += mesh->nb_vt;
			last_index = j;
			model->meshs->mesh[model->meshs->size] = mesh;
			model->meshs->size++;
			mesh = create_mesh();
			mem_len_indices = BUFFER_OBJ * sizeof(GLuint);
			mem_len_indexed_v = BUFFER_OBJ * sizeof(GLfloat);
			mem_len_indexed_vn = BUFFER_OBJ * sizeof(GLfloat);
			mem_len_indexed_vt = BUFFER_OBJ * sizeof(GLfloat);
			mem_len_v = BUFFER_OBJ * sizeof(GLfloat);
			mem_len_vt = BUFFER_OBJ * sizeof(GLfloat);
			mem_len_vn = BUFFER_OBJ * sizeof(GLfloat);
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
	ft_printf("Cet object contient des groups\n");
	model->meshs->mesh = realloc((void *)model->meshs->mesh, sizeof(t_mesh **) * (model->meshs->size + 1));
	model->meshs->mesh[model->meshs->size] = mesh;
	model->meshs->size++;
	printf("Pars end\n");
	uint32_t i = 0;
	printf("%i\n", model->meshs->size);
	while (i < model->meshs->size)
	{
		mesh_buffers(model->meshs->mesh[i], model->flag);
		i++;
	}
	if (tex)
		model->flag |= F_TEXTURE;
	return (true);
}

bool		parsing_mtl(t_model *model, const char *path_mtl)
{
	int			fd;
	char		*line;
	char		type[10];
	char		path[1024];
	char		name[1024];
	GLuint		map_id;

	bzero(name, 1024);
	fd = open(path_mtl, O_RDONLY);
	if (!fd || fd < 0)
		return (false);

(void)model;
	line = NULL;
	t_material *material;

	//if (!(material = material_construct()))
	//	return (false);
	while (get_next_line(fd, &line))
	{
		map_id = 0;
		sscanf(line, "%s ", type);
	//	printf("%s\n", line);
		if (!strcmp(type, "newmtl"))
		{
			if (material)
				model->materials->add(model->materials, material);
			sscanf(line, "%s %s\n", type, name);
			material = material_construct(name);
		}
		else if (!strcmp(type, "Ka"))
			sscanf(line, "%s %f %f %f\n", type, &material->ambient.x, &material->ambient.y, &material->ambient.z);
		else if (!strcmp(type, "Kd"))
			sscanf(line, "%s %f %f %f\n", type, &material->diffuse.x, &material->diffuse.y, &material->diffuse.z);
		else if (!strcmp(type, "Ks"))
			sscanf(line, "%s %f %f %f\n", type, &material->specular.x, &material->specular.y, &material->specular.z);
		else if (!strcmp(type, "Ns"))
			sscanf(line, "%s %f", type, &material->shininess);
		else if (!strcmp(type, "d"))
			sscanf(line, "%s %f", type, &material->transparency);
		else if (!strcmp(type, "map_Ka"))
		{
			sscanf(line, "%s %s", type, path);
			char *path_tex = ft_strjoin((const char *)model->path, path);
			if (!(map_id = model->textures->add(model->textures, path_tex)))
				return (false);
			material->set_map(material, MATERIAL_MAP_AMBIENT, map_id);
			ft_printf("map_Ka set %s\n", path_tex);
		}
		else if (!strcmp(type, "map_Kd"))
		{
			sscanf(line, "%s %s", type, path);
			char *path_tex = ft_strjoin((const char *)model->path, path);
			if (!(map_id = model->textures->add(model->textures, path_tex)))
				return (false);
			material->set_map(material, MATERIAL_MAP_DIFFUSE, map_id);
			ft_printf("Map_diffuse set  %s\n", path_tex);
		}
		else if (!strcmp(type, "map_Ks"))
		{
			sscanf(line, "%s %s", type, path);
			char *path_tex = ft_strjoin((const char *)model->path, path);
			if (!(map_id = model->textures->add(model->textures, path_tex)))
				return (false);
			material->set_map(material, MATERIAL_MAP_SPECULAR, map_id);
			ft_printf("Map_s set\n");
		}
		else if (!strcmp(type, "map_Ns"))
		{
			sscanf(line, "%s %s", type, path);
			char *path_tex = ft_strjoin((const char *)model->path, path);
			if (!(map_id = model->textures->add(model->textures, path_tex)))
				return (false);
			material->set_map(material, MATERIAL_MAP_SHININESS, map_id);
			ft_printf("Map_shininess set %s\n", path_tex);
		}
		else if (!strcmp(type, "norm"))
		{
			sscanf(line, "%s %s", type, path);
			char *path_tex = ft_strjoin((const char *)model->path, path);
			if (!(map_id = model->textures->add(model->textures, path_tex)))
				return (false);
			material->set_map(material, MATERIAL_MAP_NORMAL, map_id);
			ft_printf("Map_normal set %s\n", path_tex);
		}
		if (material)
			model->materials->add(model->materials, material);
		ft_memdel((void *)&line);
	}
	return (true);
}
