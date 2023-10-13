#version 330 core

// constants
float AMBIENT=.2f;
float SPECULAR=1.8f;

// defining outputs
out vec4 FragColor;

// defining inputs
in vec3 color;
in vec3 normal;
in vec2 texCoord;
in vec3 globalPos;

// defing uniforms
uniform sampler2D diffuse0;// diffuse texture
uniform sampler2D specular0;// specular texture

uniform vec4 lightColor;
uniform vec3 lightPos;

uniform vec3 camPos;

void main()
{
	// directions
	vec3 normal_=normalize(normal);
	
	vec3 lightDirection=normalize(lightPos-globalPos);
	vec3 viewDirection=normalize(camPos-globalPos);
	vec3 reflectinDirection=reflect(-lightDirection,normal);
	
	// diffuse light
	float diffuse=max(0.f,dot(lightDirection,normal));
	
	// specular light
	float specular=SPECULAR*texture(specular0,texCoord).r*pow(max(dot(viewDirection,reflectinDirection),0.f),32);
	
	// outputing the final color
	FragColor=texture(diffuse0,texCoord)*lightColor*(AMBIENT+diffuse+specular);
}