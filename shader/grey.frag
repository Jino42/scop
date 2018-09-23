#version 330 core

#define EPSILON 0.00005f
#define M_PI 3.141592653f

# define MATERIAL_MTLLIB					(1 << 0)
# define MATERIAL_MAP_SHININESS				(1 << 1)
# define MATERIAL_MAP_NORMAL				(1 << 2)
# define MATERIAL_MAP_SPECULAR				(1 << 3)
# define MATERIAL_MAP_DIFFUSE				(1 << 4)
# define MATERIAL_MAP_AMBIENT				(1 << 5)

# define LIGHT_BASIC						(1 << 0)
# define LIGHT_DIRECTIONNAL					(1 << 1)
# define LIGHT_POINT						(1 << 2)
# define LIGHT_SPOT							(1 << 3)

# define SCOP_V (1 << 1)
# define SCOP_VT (1 << 2)
# define SCOP_VN (1 << 3)
# define F_TEXTURE (1 << 4)

# define SCOP_MAX_LIGHTS 8

# define MODEL_USE_MATERIAL_PERSONNAL		(1 << 12)
# define MODEL_SAME_SCALING					(1 << 13)
# define MODEL_USE_DYNAMIQUE_TEXTURE		(1 << 14)

# define MODEL_INDEX_LIGHT_BASIC			1
# define MODEL_INDEX_LIGHT_DIRECTIONNAL		0
# define MODEL_INDEX_LIGHT_POINT			1
# define MODEL_INDEX_LIGHT_SPOT				0
# define MODEL_INDEX_PLAN					2


struct t_material
{
	vec3	ambient;
	vec3	diffuse;
	vec3	specular;
	float	shininess;
	float	transparency;
	int		texture_ambient;
	int		texture_diffuse;
	int		texture_specular;
	int		texture_shininess;
	int		texture_normal;
	int		flag;
};

struct t_light
{
	vec3	position;
	vec3	direction;
	vec3	ambient;
	vec3	diffuse;
	vec3	specular;
	float	constent;
	float	linear;
	float	quadratic;
	float	spot_little_radius;
	float	spot_big_radius;
	int		type;
	float	intensity;
};

out vec4 FragColor;

in vec3 position;
in vec2 uv;
in vec3 normal;
in vec3 vn_out;
in vec4 gl_FragCoord;
flat in float vertex_id;

uniform t_light		u_light[SCOP_MAX_LIGHTS];
uniform vec3		u_cameraPosition;
uniform t_material	u_material;
uniform sampler2D	u_texture;
uniform float		u_time;
uniform int			u_obj_flag;

vec3 ambient;
vec3 diffuse;
vec3 specular;
vec3 dir_light;
vec3 dir_view;
vec3 norm;
vec3 result_color;
vec4 textureAmbient;
t_material material;

vec3	phong(t_light light)
{
	vec3 recult_phong;
	ambient = material.ambient * light.ambient;

	norm = normalize(normal);
	if (light.type == LIGHT_DIRECTIONNAL)
		dir_light = normalize(-light.direction);
	else
		dir_light = normalize(light.position - position);

	diffuse = max(dot(norm, dir_light), 0) * material.diffuse * light.diffuse;

	vec3 reflection = reflect(dir_light, norm);
	dir_view = normalize(u_cameraPosition - position);

	float angleReflection = max(dot(dir_view, reflection), 0.f);
	specular = (pow(angleReflection, material.shininess) * material.specular) * light.specular;

	if (light.type == LIGHT_SPOT)
	{

		float theta = dot(-dir_light, normalize(light.direction)) * 180 / M_PI;
		float epsilon = (light.spot_little_radius - light.spot_big_radius);
		float intensity = clamp((theta - light.spot_big_radius) / epsilon, 0.0, 1.0);
		diffuse  *= intensity;
		specular *= intensity;
	}

	recult_phong = (ambient + diffuse + specular) * light.intensity;

	if (light.type == LIGHT_POINT)
	{
		float distance    = length(light.position - position);
		float attenuation = 1.0 / (light.constent + light.linear * distance +
							light.quadratic * (distance * distance));
		recult_phong *= attenuation;
	}
	return (recult_phong);
}

void main()
{
	material = u_material;
	material.ambient = vec3(vertex_id);
	material.diffuse = vec3(vertex_id);
	if (material.texture_diffuse == 1)
	{
		if ((u_obj_flag & SCOP_VT) == 0)
			textureAmbient = texture(u_texture, vec2(position.x, position.y));
		else
			textureAmbient = texture(u_texture, uv);
		textureAmbient = texture(u_texture, uv);
		material.diffuse = textureAmbient.rgb;
		material.ambient = textureAmbient.rgb * 0.1;
		material.specular = textureAmbient.rgb;
	}

	for (int i = 0; i < SCOP_MAX_LIGHTS; i++)
		result_color += phong(u_light[i]);

	FragColor = vec4(result_color, 1.f);
}
