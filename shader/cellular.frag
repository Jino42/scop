#version 330 core

out vec4 FragColor;

in vec2	uv;
vec2	scaled_uv;

uniform float u_time;



vec2 random2(vec2 p)
{
    return fract(sin(vec2(dot(p, vec2(127.1,311.7)), dot(p, vec2(269.5,183.3)))) * 43758.5453);
}

void main()
{
    vec3 color = vec3(0.f);


	vec2 scaled_uv = uv * 40.f;

    vec2 i_uv = floor(scaled_uv);
    vec2 f_uv = fract(scaled_uv);
    float m_dist = 1.f;

    for (int y = -1; y <= 1; y++)
    {
        for (int x = -1; x <= 1; x++)
        {
            vec2 neighbor = vec2(float(x), float(y));
            vec2 point = random2(i_uv + neighbor);
            point = 0.5f + 0.5f * sin(u_time + 6.2831f * point);

            vec2 diff = neighbor + point - f_uv;

            float dist = length(diff);

            m_dist = min(m_dist, dist);
        }
    }
	color += m_dist;
	color += 1.f -step(0.02f, m_dist);
	FragColor = vec4(color, 1.0);
}
