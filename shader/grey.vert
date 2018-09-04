#version 330 core

layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec3 vn;
layout (location = 2) in vec2 vt;
layout (location = 3) in float nb;

uniform mat4 MVP;
uniform mat4 M;

out vec3 position;
out vec2 uv;
out vec3 vn_out;
out vec3 normal;
flat out float vertex_id;

void main()
{
	gl_Position =  MVP * vec4(vertexPos, 1.0f);
	normal = mat3(transpose(inverse(M))) * vn;
	position = vec3(M * vec4(vertexPos, 1.f));
	uv = vt;
	vn_out = vn;
	vertex_id = nb;
}
