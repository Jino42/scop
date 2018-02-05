#version 330 core

#define EPSILON 0.00005f

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
	vec3	ambient;
	vec3	diffuse;
	vec3	specular;
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
	//newMaterial.ambient = texture(testTexture, uv).rgb;
	newMaterial.diffuse = texture(testTexture, uv).rgb;
	//newMaterial.specular = vec3(1.f, 0.689344f, 0.154515f);

	ambient = newMaterial.ambient * light.ambient;

	norm = normalize(normal);
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
