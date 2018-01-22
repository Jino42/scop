#version 330 core

out vec4 FragColor;

in vec3 position;
in vec3 normal;

uniform vec3 objectColor;
uniform vec3 lightPosition;
uniform vec3 cameraPosition;

float intensityAmbiant = 0.15;
vec3 lightAmbiant;
vec3 lightDiffuse;
vec3 lightSpecular;
vec3 lightColor = vec3(1.1f, 1.1f, 1.1f);
vec3 light;
vec3 lightDir;
vec3 cam_to_obj;
vec3 norm;

void main()
{
	lightAmbiant = lightColor * lightAmbiant;

	norm = normalize(normal);
	lightDir = normalize(position - lightPosition);

	lightDiffuse = lightColor * max(dot(norm, -lightDir), 0);

	vec3 reflection = reflect(lightDir, norm);
	cam_to_obj = normalize(position - cameraPosition);

	float angleReflection = max(dot(-cam_to_obj, reflection), 0);
	if (angleReflection > 0.00005f)
		lightSpecular = vec3(0.f, 0.f, 0.f);
	else
		lightSpecular = lightColor * pow(angleReflection, 64);

	light = (lightAmbiant + lightDiffuse + lightSpecular) * objectColor;
	FragColor = vec4(light, 1.f);
}
