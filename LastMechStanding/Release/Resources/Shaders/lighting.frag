#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct DirLight {
	vec3 direction;
	vec3 ambient, diffuse, specular;
};

struct PointLight {    
    vec3 position;
    float constant, linear, quadratic;
	vec3 ambient, diffuse, specular;
};

#define NR_POINT_LIGHTS 4	// number of point lights in the scene

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 color;

uniform vec3 viewPos;
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform Material material;

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	
	// diffuse component:
    float diff = max(dot(normal, lightDir), 0.0);

	// specular component:
	vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	// result:
	vec3 ambient = light.ambient * vec3(texture2D(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture2D(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture2D(material.specular, TexCoords));
    return (ambient + diffuse + specular);
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
	
	// diffuse component:
    float diff = max(dot(normal, lightDir), 0.0);

	// specular component:
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	// attenuation (light intensity loss over distance):
    float dist = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * dist + light.quadratic * (dist * dist)); 

	// result:
    vec3 ambient = light.ambient * vec3(texture2D(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture2D(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture2D(material.specular, TexCoords));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
	
    vec3 result = calcDirLight(dirLight, norm, viewDir);
    for(int i = 0; i < NR_POINT_LIGHTS; i++) {
        result += calcPointLight(pointLights[i], norm, FragPos, viewDir);    
	}

	color = vec4(result, 1.0);
}