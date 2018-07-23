#version 330 core

#define EPSILON 0.00005f

# define MATERIAL_MTLLIB			(1 << 0)
# define MATERIAL_MAP_SHININESS		(1 << 1)
# define MATERIAL_MAP_NORMAL		(1 << 2)
# define MATERIAL_MAP_SPECULAR		(1 << 3)
# define MATERIAL_MAP_DIFFUSE		(1 << 4)
# define MATERIAL_MAP_AMBIENT		(1 << 5)

# define LIGHT_BASIC				(1 << 0)
# define LIGHT_DIRECTIONNAL			(1 << 1)
# define LIGHT_POINT				(1 << 2)

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
	int		type;
};

out vec4 FragColor;

in vec3 position;
in vec2 uv;
in vec3 normal;

uniform t_light		light;
uniform vec3		cameraPosition;
uniform t_material	material;
uniform sampler2D	testTexture;

float intensityAmbient = 0.15;
vec3 ambient;
vec3 diffuse;
vec3 specular;
vec3 lightColor = vec3(1.f, 1.f, 1.f);
vec3 lightDir;
vec3 cam_to_obj;
vec3 norm;
vec3 resultColor;

t_material newMaterial;

void main()
{
	newMaterial = material;
	if (newMaterial.texture_diffuse == 1)
		newMaterial.diffuse = texture(testTexture, uv).rgb;

	ambient = newMaterial.ambient * light.ambient;

	norm = normalize(normal);
	if (light.type == LIGHT_DIRECTIONNAL)
		lightDir = normalize(light.direction);
	else
		lightDir = normalize(position - light.position);

	diffuse = max(dot(norm, -lightDir), 0) * newMaterial.diffuse * light.diffuse;

	vec3 reflection = reflect(-lightDir, norm);
	cam_to_obj = normalize(position - cameraPosition);

	float angleReflection = max(dot(-cam_to_obj, reflection), 0);
	specular = (pow(angleReflection, newMaterial.shininess) * newMaterial.specular) * light.specular;

	resultColor = (ambient + diffuse + specular);
	FragColor = vec4(resultColor, 1.f);
	//FragColor = texture(testTexture, uv);
}
