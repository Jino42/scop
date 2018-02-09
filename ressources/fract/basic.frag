#version 330 core

#define EPSILON 0.00005f

struct t_material
{
	vec3	ambient;
	vec3	diffuse;
	vec3	specular;
	float	shininess;
	float	transparency;
	int		texture_ambient;
	int		texture_diffuse;
	int		texture_specular;
	int		texture_shininess;
	int		texture_normal;
	int		flag;
};

struct t_light
{
	vec3	position;
	vec3	ambient;
	vec3	diffuse;
	vec3	specular;
};

float DE(vec3 pos) {
	float Power = 8.0;
	vec3 z = pos;
    float dr = 1.0;
    float r = 0.0;
    for (int i = 0; i < 10 ; i++)
	{
        r = length(z);
        if (r > 4.0)
			break;

        // convert to polar coordinates
        float theta = acos(z.z / r);
        float phi = atan(z.y,z.x);
        dr =  pow(r, Power - 1.0) * Power * dr + 1.0;

        // scale and rotate the point
        float zr = pow(r, Power);
        theta = theta * Power;
        phi = phi * Power;

        // convert back to cartesian coordinates
        z = zr * vec3(sin(theta) * cos(phi), sin(phi) * sin(theta), cos(theta));
        z += pos;
    }
    return (0.5 * log(r) * r / dr);
}

vec2    rotate(vec2 pos, float angle)
{
   return (vec2(
           pos.x * cos(angle) - pos.y * sin(angle),
           pos.y * cos(angle) + pos.x * sin(angle)
       ));
}

float    intersect_plane(vec3 pos)
{
   return (pos.y);
}

float    intersect_sphere(vec3 pos, float radius)
{
   return (length(pos) - radius);
}

float    intersect_box(vec3 pos, vec3 size)
{
   return (length(max(abs(pos) - size, 0.0)));
}

float     map(vec3 pos)
{
   //pos = vec3(rotate(pos.yx, pos.z * cos(iTime) * 0.02), pos.z);
  // pos = vec3(pos.x, rotate(pos.yz, pos.x * cos(iTime) * 0.02));
   //float planeDist = intersect_plane(pos);


   //pos = vec3(rotate(pos.xy, pos.z * cos(iTime) * 0.02), pos.z);

   //pos = mod(vec3(pos.x, pos.y, pos.z) + 10.0, 20.0) - 10.0;

   return DE(pos);//min(planeDist, intersect_box(pos, vec3(2, 2, 2)));
}

uniform t_light		light;
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
	mat4 nV = oV;
	nV[3][0] = 0;
	nV[3][1] = 0;
	nV[3][2] = 0;
	mat4 nM = mat4(1.0);
	nM[3][0] = oV[3][0];
	nM[3][1] = oV[3][1];
	nM[3][2] = oV[3][2];
   vec2 nuv = -1.0 + uv.xy * 2;
   vec3 camPos;
   vec3 tmp = normalize(vec3(nuv, 1.));
   vec3 camDi = normalize(position - cameraPosition);
   float angle = 0.5;

   // Time varying pixel color
  //vec3 dir = vec3(vec4(camDi, 1.0) * oV);
  vec3 dir = vec3(vec4(tmp, 1.0) * nV);
   vec4 color = vec4(0.4f, 0.4f, 0.4f, 0.0f);
   vec3 pos = cameraPosition;
   lightDir = position - light.position;
   for (int i = 0; i < 50; i++)
   {
       float d = map(pos);
       if (d < 0.01f)
       {
           //color = material(pos);
        	vec2 Dd = vec2(0.01, 0.0);
           	vec3 n = normalize(vec3(DE(pos+Dd.xyy)-DE(pos-Dd.xyy),
                                	DE(pos+Dd.yxy)-DE(pos-Dd.yxy),
                                    DE(pos+Dd.yyx)-DE(pos-Dd.yyx)));
           //float fc = fract(length(pos - camPos));
           //color = vec3(fc, fc, fc);
           color = vec4(0.25, 0.5, 1.0 / 64.0 * i, 1.) * dot(n, -lightDir);
           break ;
       }
       pos += d * dir;
   }

   // Output to screen
   fragColor = color;
   //fragColor = color;
}
