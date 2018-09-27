#version 330 core

out vec4 FragColor;

in vec2	uv;
vec2	scaled_uv;

uniform float u_time;

vec2 random2(vec2 p)
{
    return sin(vec2(u_time) + 6.2831f *
		fract(sin(vec2(
			dot(p, vec2(127.1f, 311.7f)),
			dot(p, vec2(269.5f, 183.3f))
			)) * 43758.5453f));
}

void main()
{
    vec3 color = vec3(0.f);
	vec2 scaled_uv = uv * 40.f;
    vec2 i_uv = floor(scaled_uv);
    vec2 f_uv = fract(scaled_uv);
    float m_dist = 1.f;

	int y;
	int x;
	vec2 neighbor;
	vec2 point;
	vec2 diff;
	float dist;

	y = -1;
    while (y <= 1)
    {
		x = -1;
        while (x <= 1)
        {
            neighbor = vec2(float(x), float(y));
            point = 0.5f + 0.5f * random2(i_uv + neighbor);
            diff = neighbor + point - f_uv;
            dist = length(diff);
            m_dist = min(m_dist, dist);
			x++;
        }
		y++;
    }
	color += m_dist;
	if (length(m_dist) < 0.02f)
		color = vec3(1.f);
	FragColor = vec4(color, 1.0);
}
