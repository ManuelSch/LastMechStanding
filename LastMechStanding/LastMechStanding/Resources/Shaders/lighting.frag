#version 330 core

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light {
    vec3 ambient, diffuse, specular;
    float constant, linear, quadratic;
    vec3 position;
    vec3  direction;
    float cutOff;	// spotlight angle
    float outerCutOff;	// outer spotlight angle (for soft spotlight cone edges)
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

out vec4 color;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
	// ambient component:
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

	// diffuse component:
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

	// specular component:
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
	
	// soft spotlight cone edges:
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon   = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0); 
	diffuse  *= intensity;
	specular *= intensity;

	// light distance (attenuation):
	float dist = length(light.position - FragPos);
	float attenuation = 1.0f / (light.constant + light.linear * dist + light.quadratic * (dist * dist));
	diffuse  *= attenuation;
	specular *= attenuation; 

	color = vec4(ambient + diffuse + specular, 1.0f);
}