#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

void main()
{
	gl_Position = position;
	v_TexCoord = texCoord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;
uniform vec4 lightColor;
uniform vec3 lightPosition;
uniform vec3 normal;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);

	vec3 lightVector = normalize(lightPosition - vec3(v_TexCoord[0], v_TexCoord[1], 0.0));

	float brightness = dot(lightVector, normal);

	color = vec4(texColor[0], texColor[1], texColor[2], brightness) * lightColor;
};