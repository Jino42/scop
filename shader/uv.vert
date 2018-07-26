#version 330 core

layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec3 vn;
layout (location = 2) in vec2 vt;

out vec2 uv;

void main()
{
    gl_Position = vec4(vec3(vertexPos), 1.0);
    uv = vt;
}
