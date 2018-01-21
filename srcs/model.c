
#include "scop.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void		model_render(t_model *model, t_matrix *view, t_matrix *projection)
{
	t_asset *asset;
	t_matrix temp, mvp;

	asset = model->asset;
	asset->shader->use(asset->shader);
	model->transform.matrix[0][0] = 0.005;
	model->transform.matrix[1][1] = 0.005;
	model->transform.matrix[2][2] = 0.005;
	temp = matrix_get_mult_matrix(&model->transform, view);
	mvp = matrix_get_mult_matrix(&temp, projection);
	glUniformMatrix4fv(
			glGetUniformLocation(asset->shader->program, "MVP"),
			1, GL_FALSE, &mvp.matrix[0][0]);

	glBindVertexArray(asset->VAO);
	glDrawElements(GL_TRIANGLES, asset->nb_indices, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void		asset_buffers(t_asset *asset)
{
	glGenBuffers(1, &asset->EBO);
	glGenVertexArrays(1, &asset->VAO);

	glBindVertexArray(asset->VAO);

	if (asset->flag & SCOP_V)
	{
		ft_printf("Set buffer : V\n");
		glGenBuffers(1, &asset->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, asset->VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (asset->nb_indices) * 3, asset->indexed_v, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	if (asset->flag & SCOP_VN)
	{
		ft_printf("Set buffer : VN\n");
		glGenBuffers(1, &asset->VNBO);
		glBindBuffer(GL_ARRAY_BUFFER, asset->VNBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (asset->nb_indices) * 3, asset->indexed_vn, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	if (asset->flag & SCOP_VT)
	{
		ft_printf("Set buffer : VT\n");
		glGenBuffers(1, &asset->VTBO);
		glBindBuffer(GL_ARRAY_BUFFER, asset->VTBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (asset->nb_indices) * 2, asset->indexed_vt, GL_STATIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, asset->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * asset->nb_indices, asset->indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

t_asset	*asset_create(const char *path_obj)
{
	t_asset		*asset;

	if (!(asset = ft_memalloc(sizeof(t_asset))))
		return (NULL);
	asset->type_draw = GL_POINTS;
	if (!obj_pars(asset, path_obj))
	{
		ft_memdel((void *)&asset);
		return (NULL);
	}
	if (DEBUG)
	{
		int fd = open("osef", O_RDWR | O_TRUNC);
		int i = 0;
		dprintf(fd, "cc");
		while (i < asset->nb_v)
		{
			dprintf(fd, "v %f %f %f\n", asset->v[i * 3], asset->v[i * 3 + 1], asset->v[i * 3 + 2]);
			i++;
		}
		i = 0;
		while (i < asset->nb_vt)
		{
			dprintf(fd, "vt %f %f\n", asset->vt[i * 2], asset->vt[i * 2 + 1]);
			i++;
		}
		i = 0;
		while (i < asset->nb_vn)
		{
			dprintf(fd, "vn %f %f %f\n", asset->vn[i * 3], asset->vn[i * 3 + 1], asset->vn[i * 3 + 2]);
			i++;
		}
		i = 0;
		while (i < asset->nb_indices)
		{
			dprintf(fd, "v %f %f %f\n",
			asset->indexed_v[i],
			asset->indexed_v[i+1],
			asset->indexed_v[i+2]);
			i+=3;
		}
		dprintf(fd, "%d\n", asset->nb_v);
		dprintf(fd, "%d\n", asset->nb_indices);
		dprintf(fd, "%d\n", asset->nb_faces);
	}
	asset_buffers(asset);
	if (!(asset->texture = texture_construct("img/prevo.img")))
		return (NULL); ////////DAFUQ
	return (asset);
}

void	*model_destroy(t_model **model)
{
	t_asset *asset;

	if (!model || !*model)
		return (NULL);
	if ((*model)->asset)
	{
		asset = (*model)->asset;
		if (asset->shader)
			shader_destroy(&asset->shader);
		if (asset->texture)
			texture_destroy(&asset->texture);
	}
	ft_memdel((void *)model);
	return (NULL);
}

t_model	*model_construct(const char *obj_path,
						const char *shader_vert_path,
						const char *shader_frag_path)
{
	t_model		*model;

	if (!(model = ft_memalloc(sizeof(t_model))))
		return (model_destroy(&model));
	if (!(model->asset = asset_create(obj_path)))
		return (model_destroy(&model));
	if (!(model->asset->shader = shader_construct(shader_vert_path, shader_frag_path)))
		return (model_destroy(&model));
	model->transform = matrix_get_identity();
	model->render = &model_render;
	return (model);
}
