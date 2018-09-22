#version 330 core

# define SCOP_V (1 << 1)
# define SCOP_VT (1 << 2)
# define SCOP_VN (1 << 3)
# define F_TEXTURE (1 << 4)

#define M_PI 3.141592653f

layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec3 vn;
layout (location = 2) in vec2 vt;
layout (location = 4) in vec3 u_axis;

uniform mat4	MVP;
uniform mat4	M;
uniform int		u_obj_flag;

out vec3 position;
out vec3 normal;
out vec2 uv;

vec2	plane_mapping()
{
	float	u;
	float	v;
	vec3	v_axis;

	v_axis = cross(u_axis, vn);
	u = dot(vertexPos, u_axis);
	v = dot(vertexPos, v_axis);
	return (vec2(u, v) / 2);
}

void main()
{
	gl_Position =  MVP * vec4(vertexPos, 1.0f);
	normal = mat3(transpose(inverse(M))) * vn;
	position = vec3(M * vec4(vertexPos, 1.f));
	if ((u_obj_flag & SCOP_VT) == 0)
		uv = plane_mapping();
	else
		uv = vt;
}
