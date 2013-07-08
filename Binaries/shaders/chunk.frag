#version 330

in vec3 exColor;
in vec3 exTexCoord;

out vec3 outColor;

uniform sampler2DArray uniTex;

void main()
{
	outColor = texture(uniTex, exTexCoord).rgb * exColor * 0.80;
}