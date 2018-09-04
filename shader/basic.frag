#version 330 core

#define EPSILON 0.00005f
#define M_PI 3.141592653f

# define MATERIAL_MTLLIB			(1 << 0)
# define MATERIAL_MAP_SHININESS		(1 << 1)
# define MATERIAL_MAP_NORMAL		(1 << 2)
# define MATERIAL_MAP_SPECULAR		(1 << 3)
# define MATERIAL_MAP_DIFFUSE		(1 << 4)
# define MATERIAL_MAP_AMBIENT		(1 << 5)

# define LIGHT_BASIC				(1 << 0)
# define LIGHT_DIRECTIONNAL			(1 << 1)
# define LIGHT_POINT				(1 << 2)
# define LIGHT_SPOT					(1 << 3)

# define SCOP_V (1 << 1)
# define SCOP_VT (1 << 2)
# define SCOP_VN (1 << 3)
# define F_TEXTURE (1 << 4)

# define MODEL_USE_MATERIAL_PERSONNAL		(1 << 12)
# define MODEL_SAME_SCALING					(1 << 13)
# define MODEL_USE_DYNAMIQUE_TEXTURE		(1 << 14)

# define MODEL_INDEX_LIGHT_BASIC			1
# define MODEL_INDEX_LIGHT_DIRECTIONNAL		0
# define MODEL_INDEX_LIGHT_POINT			1
# define MODEL_INDEX_LIGHT_SPOT				0
# define MODEL_INDEX_PLAN					2


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
	vec3	direction;
	vec3	ambient;
	vec3	diffuse;
	vec3	specular;
	float	constent;
	float	linear;
	float	quadratic;
	float	spot_little_radius;
	float	spot_big_radius;
	int		type;
};

out vec4 FragColor;

in vec3 position;
in vec2 uv;
in vec3 normal;
in vec4 gl_FragCoord;

uniform t_light		light;
uniform vec3		cameraPosition;
uniform t_material	material;
uniform sampler2D	testTexture;
uniform float		far;
uniform float		near;
uniform float		time;
uniform int			obj_flag;

float intensityAmbient = 0.15;
vec3 ambient;
vec3 diffuse;
vec3 specular;
vec3 lightColor = vec3(1.f, 1.f, 1.f);
vec3 lightDir;
vec3 cam_to_obj;
vec3 norm;
vec3 resultColor;
float textureTransparency;
vec4 textureAmbient;
t_material newMaterial;

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // back to NDC
    return (2.0 * near * far) / (far + near - z * (far - near));
}

void main()
{
	textureTransparency = 1.f;
	newMaterial = material;
	if (newMaterial.texture_diffuse == 1)
	{
		if ((obj_flag & SCOP_VT) == 0)
			textureAmbient = texture(testTexture, vec2(position.x, position.y));
		else
			textureAmbient = texture(testTexture, uv);
		newMaterial.diffuse = textureAmbient.rgb;
		newMaterial.ambient = textureAmbient.rgb * 0.1;
		newMaterial.specular = textureAmbient.rgb;
		/*if (textureAmbient.a < 0.1)
			discard ;
		textureTransparency = texture(testTexture, uv).a;*/
	}

	ambient = newMaterial.ambient * light.ambient;

	norm = normalize(normal);
	if (light.type == LIGHT_DIRECTIONNAL)
		lightDir = normalize(light.direction);
	else
		lightDir = normalize(position - light.position);

	diffuse = max(dot(norm, -lightDir), 0) * newMaterial.diffuse * light.diffuse;

	vec3 reflection = reflect(-lightDir, norm);
	cam_to_obj = normalize(position - cameraPosition);

	float angleReflection = max(dot(-cam_to_obj, reflection), 0.f);
	specular = (pow(angleReflection, newMaterial.shininess) * newMaterial.specular) * light.specular;

	if (light.type == LIGHT_SPOT)
	{

		float theta = dot(lightDir, normalize(light.direction)) * 180 / M_PI;
		float epsilon = (light.spot_little_radius - light.spot_big_radius);
		float intensity = clamp((theta - light.spot_big_radius) / epsilon, 0.0, 1.0);
		diffuse  *= intensity;
		specular *= intensity;
	}

	resultColor = (ambient + diffuse + specular);

	if (light.type == LIGHT_POINT)
	{
		float distance    = length(light.position - position);
		float attenuation = 1.0 / (light.constent + light.linear * distance +
    		    			light.quadratic * (distance * distance));
		resultColor *= attenuation;
	}

	FragColor = vec4(resultColor, textureTransparency);
/*
	float depth = LinearizeDepth(gl_FragCoord.z) / far;
	FragColor = vec4(vec3(depth), 1.f);
*/
	//FragColor = texture(testTexture, uv);
}
