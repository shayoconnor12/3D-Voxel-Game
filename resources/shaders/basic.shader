#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 vTexCoord;

uniform int uDimension;
uniform vec2 uOffset;

uniform mat4 uCameraMatrix;
uniform mat4 uModelMatrix;

void main()
{
	vec3 newPosition = position.xyz;
	gl_Position = uCameraMatrix * uModelMatrix * vec4(newPosition, 1.0f);
	vTexCoord = 1 - ((texCoord/uDimension) + uOffset);
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 colour;

in vec2 vTexCoord;

uniform sampler2D uTexture;

void main()
{
	vec4 texColour = texture(uTexture, vTexCoord);
	colour = texColour;
}; 