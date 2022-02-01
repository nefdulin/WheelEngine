#type vertex
#version 330 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec2 a_TexCoords;

out vec2 texCoord;

uniform mat4 u_MVP;

void main()
{
	texCoord = a_TexCoords;
	gl_Position = u_MVP * vec4(a_Position, 1.0);
}

#type pixel
#version 330 core

in vec2 texCoord;
out vec4 color;

uniform sampler2D u_Texture;
uniform vec4 u_Color;

void main()
{
	color = texture(u_Texture, texCoord) * u_Color;
}
