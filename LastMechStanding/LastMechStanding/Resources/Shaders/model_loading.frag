#version 330 core

struct Material
{
    sampler2D texture_diffuse1;
    sampler2D texture_diffuse2;
    sampler2D texture_diffuse3;
    sampler2D texture_diffuse4;
    sampler2D texture_diffuse5;
    sampler2D texture_diffuse6;
    sampler2D texture_diffuse7;
    sampler2D texture_specular1;
    sampler2D texture_specular2;
    sampler2D texture_specular3;
    sampler2D texture_specular4;
    sampler2D texture_specular5;
    sampler2D texture_specular6;
    sampler2D texture_specular7;
    float shininess;
};

struct DirLight {
	vec3 direction;
	vec3 ambient, diffuse, specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
in vec4 FragPosLightSpace;

layout (location = 0) out vec4 color;
layout (location = 1) out vec4 brightColor;

uniform vec3 viewPos;
uniform DirLight dirLight;
uniform Material material;
uniform sampler2D shadowMap;

float calcShadow(vec4 fragPosLightSpace)
{
    // perform perspective divide (returns light-space position in the range [-1,1]):
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;

	// projCoords to the range [0,1]:
	projCoords = projCoords * 0.5 + 0.5; 
	
	// calculate closest depth from the light's point of view:
	float closestDepth = texture(shadowMap, projCoords.xy).r; 
	float currentDepth = projCoords.z;

	// offset bias for avoiding shadow acne:
	float bias = max(0.005 * (1.0 - dot(Normal, dirLight.direction)), 0.005); 
	 
    float shadow = 0.0;
    if(projCoords.z > 1.0) {
		// if fragment is outside of far plane -> fragment is lit:
        shadow = 0.0;
	}
	else {
		// PCF:
		vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
		for(int x = -1; x <= 1; ++x)
		{
			for(int y = -1; y <= 1; ++y)
			{
				float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 

				// if currentDepth is higher than closestDepth -> fragment is in shadow:
				shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
			}    
		}
		shadow /= 9.0;
	}
	
    return shadow;
}

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	
	// ambient component:
	vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1, TexCoords));

	// diffuse component:
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse1, TexCoords));

	// specular component:
	vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.texture_specular1, TexCoords));

	// shadow map:
    float shadow = calcShadow(FragPosLightSpace);

	// result:
	return ambient + (1.0 - shadow) * (diffuse + specular);
}

void main()
{    
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
	
    vec3 result = calcDirLight(dirLight, norm, viewDir);

    color = vec4(result, 1.0f); 
	
    float brightness = dot(result, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 1.0f) {
        brightColor = color;
	}
	else {
		brightColor = vec4(0.0, 0.0, 0.0, 0.0);

		// enables "depth testing" but introduces unwanted black pixels:
		//brightColor = vec4(0.0, 0.0, 0.0, 1.0);
	}
}