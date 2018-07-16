#include "scop.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static GLboolean	shader_load_src(const char *path, char *buffer)
{
	int		fd;

	if (!(fd = open(path, O_RDONLY)))
		return (GL_FALSE);
	read(fd, buffer, MAX_SOURCE_SIZE);
	close(fd);
	return (GL_TRUE);
}

static GLboolean	shader_build_shader(GLint *shader, const GLenum shader_type,
												const char *shader_path)
{
	GLint			success;
	char			info_log[BUFFER_LOG];
	char			shader_src[MAX_SOURCE_SIZE];
	const GLchar	*shader_src_ptr;

	bzero(shader_src, MAX_SOURCE_SIZE);
	if (!shader_load_src(shader_path, shader_src))
	{
		ft_dprintf(2, "[Error load source shader of %s]\n", shader_path);
		return (GL_FALSE);
	}
	*shader = glCreateShader(shader_type);
	shader_src_ptr = shader_src;
	glShaderSource(*shader, 1, &shader_src_ptr, NULL);
	glCompileShader(*shader);
	glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		bzero(info_log, BUFFER_LOG);
		glGetShaderInfoLog(*shader, BUFFER_LOG, NULL, info_log);
		ft_dprintf(2, "[Error compilation shader :\n%s]\n", info_log);
		return (GL_FALSE);
	}
	return (GL_TRUE);
}

static GLboolean	shader_build_shader_program(t_shader *shader,
										const GLint vertex_shader,
										const GLint fragment_shader)
{
	GLint	success;
	char	info_log[BUFFER_LOG];

	shader->program = glCreateProgram();
	glAttachShader(shader->program, vertex_shader);
	glAttachShader(shader->program, fragment_shader);
	glLinkProgram(shader->program);

	glGetProgramiv(shader->program, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		bzero(info_log, BUFFER_LOG);
		glGetShaderInfoLog(shader->program, BUFFER_LOG, NULL, info_log);
		ft_dprintf(2, "[Error compilation program :\n%s]\n", info_log);
		return (GL_FALSE);
	}
	return (GL_TRUE);
}

void			shader_use(t_shader *shader)
{
	glUseProgram(shader->program);
}

void		*shader_destruct(t_shader **shader)
{
	glDeleteProgram((*shader)->program);
	ft_memdel((void **)shader);
	return (NULL);
}

t_shader		*shader_construct(const char *vertex_shader_path,
									const char *fragment_shader_path,
									const char *name)
{
	t_shader	*shader;

	if (!(shader = ft_memalloc(sizeof(t_shader))))
		return (NULL);
	GLint	vertex_shader;
	GLint	fragment_shader;

	vertex_shader = 0;
	fragment_shader = 0;
	if (!shader_build_shader(&vertex_shader, GL_VERTEX_SHADER,
											vertex_shader_path))
	{
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
		return (shader_destruct(&shader));
	}
	if (!shader_build_shader(&fragment_shader, GL_FRAGMENT_SHADER,
											fragment_shader_path))
	{
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
		return (shader_destruct(&shader));
	}
	if (!shader_build_shader_program(shader, vertex_shader, fragment_shader))
	{
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
		return (shader_destruct(&shader));
	}
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	shader->use = &shader_use;
	shader->name = strdup(name);
	return (shader);
}

bool			m_shader_add(t_m_shader *m_shader,
								const char *vertex_shader_path,
								const char *fragment_shader_path,
								const char *name)
{
	t_shader *new_shader;

	if (!(new_shader = shader_construct(vertex_shader_path, fragment_shader_path, name)))
		return (false);
	if (!(m_shader->shader = realloc(m_shader->shader, sizeof(t_shader **) * (m_shader->size + 1))))
	{
		m_shader->size = 0;
		return (false);
	}
	if (!(m_shader->shader_name = realloc(m_shader->shader_name, sizeof(char **) * (m_shader->size + 1))))
	{
		m_shader->size = 0;
		return (false);
	}
	m_shader->shader[m_shader->size] = new_shader;
	m_shader->shader_name[m_shader->size] = new_shader->name;
	m_shader->size++;
	return (true);
}

t_m_shader		*m_shader_construct()
{
	t_m_shader *m_shader;

	if (!(m_shader = ft_memalloc(sizeof(t_m_shader))))
		return (NULL);
	m_shader->add = &m_shader_add;
	return (m_shader);
}

void			*m_shader_destruct(t_m_shader **m_shader)
{
	unsigned int i;

	if (m_shader && *m_shader)
	{
		if ((*m_shader)->size)
		{
			i = 0;
			while (i < (*m_shader)->size)
			{
				shader_destruct(&(*m_shader)->shader[i]);
				i++;
			}
			ft_memdel((void **)&(*m_shader)->shader_name);
			ft_memdel((void **)&(*m_shader)->shader);
		}
		ft_memdel((void **)m_shader);
	}
	return (NULL);
}

int				m_shader_get_index(t_m_shader *m_shader, char *str)
{
	unsigned int i;

	if (!str || !(*str))
		return (0);
	i = 0;
	while (i < m_shader->size)
	{
		if (!strcmp(m_shader->shader[i]->name, str))
			return (i);
		i++;
	}
	return (0);
}


bool			m_shader_json_loop(t_m_shader *m_shader, cJSON *json_shaders)
{
	int				index;
	char			*str[3];
	cJSON			*json_shader;

	if (!json_shaders)
		return (ft_bool_error("JSON shaders is undefined ", NULL, NULL));
	json_shader = json_shaders->child;
	index = 0;
	while (json_shader)
	{
		bzero(str, sizeof(char **) * 3);
		if (!json_parse_string(json_shader, "vertex", &str[0]))
			return (dprintf(2, "JSON shader[%i]: the vertex shader is Undefined\n", index) == 0);
		if (!json_parse_string(json_shader, "fragment", &str[1]))
			return (dprintf(2, "JSON shader[%i]: the fragment shader is Undefined\n", index) == 0);
		if (!json_parse_string(json_shader, "name", &str[2]))
			return (dprintf(2, "JSON shader[%i]: the name is Undefined\n", index) == 0);
		if (!(m_shader->add(m_shader, str[0], str[1], str[2])))
			return (false);
		json_shader = json_shader->next;
		index++;
	}
	return (true);
}

bool			m_shader_json_parse(t_m_shader *m_shader, cJSON *get, const char *key)
{
	cJSON	*source;

	source = cJSON_GetObjectItemCaseSensitive(get, key);
	if (!(m_shader_json_loop(m_shader, source)))
		return (ft_bool_error("Erreur: Le parsing de t_m_shader a échoué", NULL, NULL));
	return (true);
}
