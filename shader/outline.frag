#version 330 core

out vec4 FragColor;

in vec3 position;
in vec2 uv;
in vec3 normal;

void main()
{
    FragColor = vec4(0.04, 0.28, 0.26, 1.0);
}
