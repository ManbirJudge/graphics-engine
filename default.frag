#version 330 core

// constants
float AMBIENT = 0.4f;
float SPECULAR = 1.f;

// defining outputs
out vec4 FragColor;

// defining inputs
in vec3 color;
in vec3 normal;
in vec2 texCoord;
in vec3 globalPos;

// defing uniforms
uniform sampler2D diffuse0;  // diffuse texture
uniform sampler2D specular0;  // specular texture

uniform vec4 lightColor;
uniform vec3 lightPos;

uniform vec3 camPos;

void main()
{
	// calculating directions
	vec3 normal_ = normalize(normal);

	vec3 lightDirection = normalize(lightPos - globalPos);
	vec3 viewDirection = normalize(camPos - globalPos);
	vec3 reflectinDirection = reflect(-lightDirection, normal);

	// calculating diffuse light
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// calculating specular light
	float specAmount = pow(max(dot(viewDirection, reflectinDirection), 0.0f),  16);
	float spec = specAmount * SPECULAR;

	// assigning value to the FragColor to be outputted
	FragColor =  texture(diffuse0, texCoord) * lightColor * (diffuse + AMBIENT) + (texture(specular0, texCoord).r * spec);
	// FragColor = vec4(color, 1.0f);
}