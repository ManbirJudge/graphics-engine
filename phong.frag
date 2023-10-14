#version 330 core

// constants
float AMBIENT=0.f;
float SPECULAR=1.8f;

float Il=1.f;
float gamma=1.2f;

// defining outputs
out vec4 FragColor;

// defining inputs
in vec3 color;
in vec3 normal;
in vec2 texCoord;
in vec3 globalPos;

// defing uniforms
uniform sampler2D color0;// diffuse texture
uniform sampler2D specular0;// specular map
uniform sampler2D normal0;// normal map

uniform vec4 lightColor;
uniform vec3 lightPos;

uniform vec3 camPos;

// L = light direction
// N = normal
// C = light color
// Il = Light intensity
// Bd = diffuse brigthness

float map(float value,float min1,float max1,float min2,float max2){
	return min2+(value-min1)*(max2-min2)/(max1-min1);
}

void main()
{
	// directions
	vec3 N;
	
	N.x=map(texture(normal0,texCoord).r,0,255,-1,1);
	N.y=map(texture(normal0,texCoord).g,0,255,-1,1);
	N.z=map(texture(normal0,texCoord).b,128,255,0,-1);
	
	N=normalize(N);
	
	vec3 L=normalize(lightPos-globalPos);
	vec3 viewDirection=normalize(camPos-globalPos);
	vec3 reflectinDirection=reflect(-L,N);
	
	// diffuse light
	float Bd=abs(dot(L,N))*Il;
	
	// specular light
	float Bs=SPECULAR*texture(specular0,texCoord).r*pow(max(dot(viewDirection,reflectinDirection),0.f),32);
	
	// outputing the final color
	vec4 color=texture(color0,texCoord)*lightColor*(AMBIENT+Bd);
	color.rgb=pow(color.rgb,vec3(1.f/gamma));
	
	FragColor=color;
}