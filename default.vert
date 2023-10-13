#version 330 core

layout (location = 0) in vec3 aPos;  // position
layout (location = 1) in vec3 aNormal;  // normal
layout (location = 2) in vec3 aColor;  // color
layout (location = 3) in vec2 aTexCoord;  // texture coordinates

// constants
float HEIGHT_SCALE = 2.f;

// defining outputs
out vec3 color;
out vec3 normal;
out vec3 globalPos;
out vec2 texCoord;

// defining uniforms
uniform sampler2D height0;  // height texture

uniform mat4 modelTranslationMat;
uniform mat4 modelRotationMat;
uniform mat4 modelScaleMat;

uniform mat4 globalMat;  // local coordinates -> global coordinates
uniform mat4 camMat;  // global coordinates -> view coordinates -> projection coordinates

void main()
{
	vec3 localPos = aPos;
	localPos.y = localPos.y + (texture2D(height0, texCoord).g * HEIGHT_SCALE);

	globalPos = vec3(
		globalMat * 
		(modelTranslationMat * modelRotationMat * modelScaleMat) * 
		vec4(localPos, 1.f)
	);
	gl_Position = camMat * vec4(globalPos, 1.0);

	// assigning values to other varaibles to be outputed
	color = aColor;
	texCoord = aTexCoord;  // (0.0, -1.0, 1.0, 0.0) * 
	normal = aNormal;
}