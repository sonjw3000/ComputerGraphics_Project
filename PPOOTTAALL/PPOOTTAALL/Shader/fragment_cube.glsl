# version 330 core

in vec3 TexCoords;

out vec4 FragColor;

uniform samplerCube skyBox;

void main()
{
	FragColor = texture(skyBox, TexCoords);
}
