
#include "scop.h"

/*
** System de flag inter mesh si uniform changê
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
bool		push_mesh(t_model *model, t_mesh *new_mesh)
{
	model->size_mesh++;
	model->mesh = realloc(model->mesh, model->size_mesh * sizeof(t_mesh *));
	model->mesh[model->size_mesh - 1] = new_mesh;
}

bool		model_loader(t_model *model,
						const char *name_obj,
						const char *path_obj)
{
	int fd;
	char *full_path_obj = ft_strjoin(name_obj, path_obj);
	t_mesh *mesh;

	fd = open(path_obj, O_RDONLY);
	if (!fd || fd < 0)
		return (false);
	if (!(mesh = ft_memalloc(t_mesh)))
		return (NULL);
	;
	return (true);
}
*/

void		model_render(t_model *model, t_cam *cam, t_light *light,
								t_matrix *view, t_matrix *projection,
								t_shader *shader, t_material *material)
{
	t_mesh **meshs;
	t_matrix temp, mvp;

	meshs = model->meshs;
/*
	if (mesh->flag & F_TEXTURE)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->texture->id);
	}*/

	shader->use(shader);

	temp = matrix_get_mult_matrix(&model->transform, view);
	mvp = matrix_get_mult_matrix(&temp, projection);
	glUniform3fv(
			glGetUniformLocation(shader->program, "light.ambient"),
			1,
			(GLfloat *)&light->ambient);
	glUniform3fv(
			glGetUniformLocation(shader->program, "light.diffuse"),
			1,
			(GLfloat *)&light->diffuse);
	glUniform3fv(
			glGetUniformLocation(shader->program, "light.specular"),
			1,
			(GLfloat *)&light->specular);
	glUniform3fv(
			glGetUniformLocation(shader->program, "light.position"),
			1,
			(GLfloat *)&light->position);
	glUniform3fv(
			glGetUniformLocation(shader->program, "material.ambient"),
			1,
			(GLfloat *)&material->ambient);
	glUniform3fv(
			glGetUniformLocation(shader->program, "material.diffuse"),
			1,
			(GLfloat *)&material->diffuse);
	glUniform3fv(
			glGetUniformLocation(shader->program, "material.specular"),
			1,
			(GLfloat *)&material->specular);
	glUniform1f(
			glGetUniformLocation(shader->program, "material.shininess"),
			material->shininess);
	glUniform3f(
			glGetUniformLocation(shader->program, "cameraPosition"),
			cam->position.x,
			cam->position.y,
			cam->position.z);
	glUniformMatrix4fv(
			glGetUniformLocation(shader->program, "MVP"),
			1, GL_FALSE, &mvp.matrix[0][0]);
	glUniformMatrix4fv(
			glGetUniformLocation(shader->program, "M"),
			1, GL_FALSE, &model->transform.matrix[0][0]);
	uint32_t i = 0;
	while (i < model->size_meshs)
	{
		glBindVertexArray(meshs[i]->VAO);
		glDrawElements(GL_TRIANGLES, meshs[i]->nb_indices, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		i++;
	}
	glUseProgram(0);
/*
	float vertices[] = {
	   -0.5f, -0.5f, 0.0f, // left
		0.5f, -0.5f, 0.0f, // right
		0.0f,  0.5f, 0.0f  // top
   };

   unsigned int VBO, VAO;
   glGenVertexArrays(1, &VAO);
   glGenBuffers(1, &VBO);
   // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
   glBindVertexArray(VAO);

   glBindBuffer(GL_ARRAY_BUFFER, VBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);

   // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
   glBindBuffer(GL_ARRAY_BUFFER, 0);


   const char *vertexShaderSource = "#version 330 core\n"
       "layout (location = 0) in vec3 aPos;\n"
       "void main()\n"
       "{\n"
       "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
       "}\0";
   const char *fragmentShaderSource = "#version 330 core\n"
       "out vec4 FragColor;\n"
       "void main()\n"
       "{\n"
       "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
       "}\n\0";
   // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
   // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
   int vertexShader = glCreateShader(GL_VERTEX_SHADER);
   glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
   glCompileShader(vertexShader);
   // check for shader compile errors
   int success;
   char infoLog[512];
   glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
   if (!success)
   {
	   glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
   }
   // fragment shader
   int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
   glCompileShader(fragmentShader);
   // check for shader compile errors
   glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
   if (!success)
   {
	   glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
   }
   // link shaders
   int shaderProgram = glCreateProgram();
   glAttachShader(shaderProgram, vertexShader);
   glAttachShader(shaderProgram, fragmentShader);
   glLinkProgram(shaderProgram);
   // check for linking errors
   glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
   if (!success) {
	   glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
   }
   glDeleteShader(vertexShader);
   glDeleteShader(fragmentShader);
     glUseProgram(shaderProgram);
	   glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	   glDrawArrays(GL_TRIANGLES, 0, 3);*/
}

void	*model_destroy(t_model **model)
{
	if (!model || !*model)
		return (NULL);
	ft_memdel((void *)model);
	return (NULL);
}

t_model	*model_construct()
{
	t_model		*model;

	if (!(model = ft_memalloc(sizeof(t_model))))
		return (NULL);
	model->type_draw = GL_POINTS;
	model->transform = matrix_get_identity();
	//model->render = &model_render;
	return (model);
}
