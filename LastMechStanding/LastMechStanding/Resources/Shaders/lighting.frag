#version 330 core

struct Material {
	sampler2D diffuse;
	vec3 specular;
	float shininess;
};

struct Light {
    vec3 ambient, diffuse, specular;
    vec3 position;
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
    vec3 specular = light.specular * (spec * material.specular);  
        
    vec3 result = ambient + diffuse + specular;
    color = vec4(result, 1.0f);
}