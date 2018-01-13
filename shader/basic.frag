#version 330 core

out vec4 FragColor;
in vec3 vertexColor;
uniform vec4 testUniform;

void main()
{
   FragColor = vec4(vertexColor.x, testUniform.y, vertexColor.z, 1.0f);
}
