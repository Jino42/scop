#version 330 core

#define EPSILON 0.00005f

struct t_material
{
	vec3	ambient;
	vec3	diffuse;
	vec3	specular;
	float	shininess;
};

out vec4 FragColor;

in vec3 position;
in vec3 normal;

uniform vec3		lightPosition;
uniform vec3		cameraPosition;
uniform t_material	material;

float intensityAmbiant = 0.15;
vec3 ambient;
vec3 diffuse;
vec3 specular;
vec3 lightColor = vec3(1.1f, 1.1f, 1.1f);
vec3 lightDir;
vec3 cam_to_obj;
vec3 norm;
vec3 resultColor;

void main()
{
	ambient = lightColor * material.ambient;

	norm = normalize(normal);
	lightDir = normalize(position - lightPosition);

	diffuse = lightColor * (max(dot(norm, -lightDir), 0) * material.diffuse);

	vec3 reflection = reflect(-lightDir, norm);
	cam_to_obj = normalize(position - cameraPosition);

	float angleReflection = max(dot(-cam_to_obj, reflection), 0);
	//if (angleReflection < 0.0005f)
	//	specular = vec3(0.f, 0.f, 0.f);
	//else
		specular = lightColor * (pow(angleReflection, 6) * material.specular);

	resultColor = (ambient + diffuse + specular);
	FragColor = vec4(resultColor, 1.f);
}
