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

# define SCOP_V								(1 << 1)
# define SCOP_VT							(1 << 2)
# define SCOP_VN							(1 << 3)
# define F_TEXTURE							(1 << 4)

# define SCOP_MAX_LIGHTS					8

# define MODEL_USE_BASIC					(1 << 10)
# define MODEL_USE_TEXTURE					(1 << 11)
# define MODEL_USE_MATERIAL_PERSONNAL		(1 << 12)
# define MODEL_SAME_SCALING					(1 << 13)
# define MODEL_ROTATE						(1 << 15)

# define MODEL_INDEX_LIGHT_BASIC			1
# define MODEL_INDEX_LIGHT_DIRECTIONNAL		0
# define MODEL_INDEX_LIGHT_POINT			1
# define MODEL_INDEX_LIGHT_SPOT				0
# define MODEL_INDEX_PLAN					2

# define TEXTURE_TRANSITION					2500
# define TEXTURE_TRANSITIONF				2500.f

struct t_material
{
	vec3	ambient;
	vec3	diffuse;
	vec3	specular;
	float	shininess;
	float	transparency;
	int		texture_diffuse;
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

out vec4				FragColor;

in vec3					position;
in vec2					uv;
in vec3					normal;
in vec4					gl_FragCoord;

uniform t_light			u_light[SCOP_MAX_LIGHTS];
uniform vec3			u_cameraPosition;
uniform t_material		u_material;
uniform t_material		u_material_personnal;
uniform sampler2D		u_texture;
uniform sampler2D		u_texture_personnal;
uniform float			u_time;
uniform int				u_timestamp;
uniform int				u_model_timestamp;

uniform int				u_obj_flag;
uniform int				u_obj_last_flag;


t_material				material;

vec3	phong(t_light light)
{
	vec3					dirLight;
	vec3					norm;
	vec3					diffuse;
	vec3					ambient;
	vec3					result_phong;
	ambient = material.ambient * light.ambient;

	norm = normalize(normal);
	if (light.type == LIGHT_DIRECTIONNAL)
		dirLight = normalize(light.direction);
	else
		dirLight = normalize(position - light.position);

	diffuse = max(dot(norm, -dirLight), 0) * material.diffuse * light.diffuse;


	result_phong = (ambient + diffuse) * light.intensity;

	if (light.type == LIGHT_POINT)
	{
		float distance    = length(light.position - position);
		float attenuation = 1.0 / (light.constent + light.linear * distance +
							light.quadratic * (distance * distance));
		result_phong *= attenuation;
	}
	return (result_phong);
}

t_material  get_material(int flag)
{
	vec4					textureAmbient;
	t_material				ret_material;
	ret_material = u_material;

	if ((flag & MODEL_USE_MATERIAL_PERSONNAL) != 0)
		ret_material = u_material_personnal;

	if ((flag & MODEL_USE_MATERIAL_PERSONNAL) != 0 && u_material_personnal.texture_diffuse == 1)
	{
		textureAmbient = texture(u_texture_personnal, uv);
		ret_material.diffuse = textureAmbient.rgb;
		ret_material.ambient = textureAmbient.rgb * 0.1;
		ret_material.specular = textureAmbient.rgb;
	}
	else if ((flag & MODEL_USE_TEXTURE) != 0)
	{
		textureAmbient = texture(u_texture, uv);
		ret_material.diffuse = textureAmbient.rgb;
		ret_material.ambient = textureAmbient.rgb * 0.1;
		ret_material.specular = textureAmbient.rgb;
	}
	return (ret_material);
}

void main()
{
	vec3					result_color;
	material = get_material(u_obj_flag);

	for (int i = 0; i < SCOP_MAX_LIGHTS; i++)
		result_color += phong(u_light[i]);

	if ((u_obj_flag & (MODEL_USE_TEXTURE | MODEL_USE_MATERIAL_PERSONNAL | MODEL_USE_BASIC)) != 0
		&& (u_timestamp - u_model_timestamp < TEXTURE_TRANSITION))
	{
		vec3 result_color2;
		material = get_material(u_obj_last_flag);;
		for (int i = 0; i < SCOP_MAX_LIGHTS; i++)
			result_color2 += phong(u_light[i]);
		float rev = (u_timestamp - u_model_timestamp) / TEXTURE_TRANSITIONF;
		result_color *= rev;
		result_color += result_color2 * (1 - rev);
	}

	FragColor = vec4(result_color, 1.f);
}
