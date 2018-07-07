#version 330 core

#define EPSILON 0.00005f

float DE(vec3 pos) {
   float Power = 8.0;
    vec3 z = pos;
    float dr = 1.0;
    float r = 0.0;
    for (int i = 0; i < 50 ; i++) {
        r = length(z);
        if (r>4.0) break;

        // convert to polar coordinates
        float theta = acos(z.z/r);
        float phi = atan(z.y,z.x);
        dr =  pow( r, Power-1.0)*Power*dr + 1.0;

        // scale and rotate the point
        float zr = pow( r,Power);
        theta = theta*Power;
        phi = phi*Power;

        // convert back to cartesian coordinates
        z = zr*vec3(sin(theta)*cos(phi), sin(phi)*sin(theta), cos(theta));
        z+=pos;
    }
    return 0.5*log(r)*r/dr;
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
   float planeDist = intersect_plane(pos);


   //pos = vec3(rotate(pos.xy, pos.z * cos(iTime) * 0.02), pos.z);

   pos = mod(vec3(pos.x, pos.y, pos.z) + 10.0, 20.0) - 10.0;

   return DE(pos);//min(planeDist, intersect_box(pos, vec3(2, 2, 2)));
}

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
   fragColor = vec4(0.7, 0.8, 0.9, 1.0);
}