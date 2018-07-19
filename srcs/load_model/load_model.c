#include "scop.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


bool		parsing_mtl(t_lm *lm, t_m_material *m_material, t_model *model)
{

	int			fd;
	char		*path_mtl;
	char		name[1024];
	char		*line;
	GLuint		map_id;
	char		type[10];
	t_material	*material;
	t_texture	*texture;

	sscanf(lm->line, "%s %s\n", lm->type, lm->buffer255);
	if (!(path_mtl = ft_strjoin(model->path, lm->buffer255)))
		return (false);

	bzero(name, 1024);
	fd = open(path_mtl, O_RDONLY);
	ft_memdel((void **)&path_mtl);
	if (!fd || fd < 0)
		return (false);

	bzero(lm->buffer255, 255);
	material = NULL;
	while (get_next_line(fd, &line))
	{
		map_id = 0;
		sscanf(line, "%s ", type);
		printf("%s\n", line);
		if (!strcmp(type, "newmtl"))
		{
			if (material)
				m_material->add(m_material, material);
			sscanf(line, "%s %s\n", type, name);
			material = material_construct(name, MATERIAL_MTLLIB);
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
			sscanf(line, "%s %s", type, lm->buffer255);
			char *path_tex = ft_strjoin((const char *)model->path, lm->buffer255);
			if (!(texture = lm->scene->m_texture->new(lm->scene->m_texture, MATERIAL_MAP_AMBIENT, path_tex)))
				return (false);
			material_set_texture(material, texture);
			ft_printf("map_Ka set %s\n", path_tex);
		}
		/*
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

		*/
		bzero(lm->buffer255, 255);
		ft_memdel((void *)&line);
	}
	if (material)
		m_material->add(m_material, material);
	return (true);
	/*

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
	*/
}


t_model		*m_model_load(t_scene *scene,
							const char *path_obj,
							const char *name)
{

	t_model	*model;

	model = model_construct(path_obj, name);
	t_lm *lm = lm_construct(scene, model, path_obj);
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
			if (!(parsing_mtl(lm, scene->m_material, model)))
				return (false);
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
	scene->m_model->add(scene->m_model, model);
	lm_destruct(&lm);
	return (model);
}
