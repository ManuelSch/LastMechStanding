#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D scene;
uniform sampler2D bloomBlur;
uniform bool bloom;
uniform vec3 backgroundColor;

void main()
{         
    vec3 result = texture2D(scene, TexCoords).rgb;      

    vec4 bloomColor = texture2D(bloomBlur, TexCoords).rgba;
	
	bloomColor -= vec4(backgroundColor, 0.0f);	// so you can use another clearColor than black
	
	// additive blending:
	if(bloom) {
		result += vec3(bloomColor);
	}

    FragColor = vec4(result, 1.0f);
	//FragColor = bloomColor;
}