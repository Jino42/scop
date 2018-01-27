#version 330 core

#define EPSILON 0.00005f

struct t_material
{
	vec3	ambient;
	vec3	diffuse;
	vec3	specular;
	float	shininess;
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
in vec3 normal;

uniform t_light		light;
uniform vec3		cameraPosition;
uniform t_material	material;

float intensityAmbient = 0.15;
vec3 ambient;
vec3 diffuse;
vec3 specular;
vec3 lightColor = vec3(1.f, 1.f, 1.f);
vec3 lightDir;
vec3 cam_to_obj;
vec3 norm;
vec3 resultColor;

void main()
{
	ambient = material.ambient * light.ambient;

	norm = normalize(normal);
	lightDir = normalize(position - light.position);

	diffuse = max(dot(norm, -lightDir), 0) * material.diffuse * light.diffuse;

	vec3 reflection = reflect(-lightDir, norm);
	cam_to_obj = normalize(position - cameraPosition);

	float angleReflection = max(dot(-cam_to_obj, reflection), 0);
	specular = (pow(angleReflection, material.shininess) * material.specular) * light.specular;

	resultColor = (ambient + diffuse + specular);
	FragColor = vec4(resultColor, 1.f);
}
