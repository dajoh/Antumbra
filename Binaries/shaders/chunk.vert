#version 330

in vec3 inColor;
in vec3 inTexCoord;
in vec3 inPosition;

out vec3 exColor;
out vec3 exTexCoord;

uniform mat4 uniMvp;

void main()
{
	exColor = inColor;
	exTexCoord = vec3(inTexCoord.x, 1 - inTexCoord.y, inTexCoord.z);
	gl_Position = uniMvp * vec4(inPosition, 1);
}