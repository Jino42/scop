#version 330 core

in vec2 uv;

uniform sampler2D tex;

out vec4 FragColor;

void main()
{
	FragColor = vec4(1.f, 1.f, 1.f, 1.f);
	FragColor = texture(tex, uv);
}
