#version 330 core

#define EPSILON 0.00005f

out vec4 fragColor;
in vec2 uv;
in vec3 position;
in mat4 oM;
in mat4 oV;
in mat4 oP;
uniform vec3		cameraPosition;
in mat4 oMVP;
vec3 lightDir;
uniform vec3 camDir;

void    main()
{
   fragColor = vec4(0.7, 0.8, 0.9, 1.0);
}
