#version 330 core

layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec3 vn;
layout (location = 2) in vec2 vt;

uniform mat4 MVP;
uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

out	vec2 uv;
out	vec3 position;
out mat4 oM;
out mat4 oV;
out mat4 oP;
out mat4 oMVP;

void main()
{
	oM = M;
	oV = V;
	oP = P;
	oMVP = MVP;
	gl_Position = vec4(vertexPos, 1.0f);
	position = vertexPos;
	uv = vt;
}
