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

uniform sampler2D woodTexture;
uniform sampler2D lightfireTexture;
uniform sampler2D darkFireTexture;
uniform sampler2D blendMapTexture;

void main()
{
	vec4 woodCol = texture(woodTexture, v_TexCoord);

	vec4 fireCol = texture(lightfireTexture, v_TexCoord);

	vec4 fireDarkCol = texture(darkFireTexture, v_TexCoord);

	vec4 blendMapColour = texture(blendMapTexture, v_TexCoord);

	float woodTextureAmount = 1 - (blendMapColour.r + blendMapColour.g + blendMapColour.b);

	vec4 woodTextureColour = texture(woodTexture, v_TexCoord) * woodTextureAmount;
	vec4 lightfireTextureColour = texture(lightfireTexture, v_TexCoord) * blendMapColour.r;
	vec4 darkFireTextureColour = texture(darkFireTexture, v_TexCoord) * blendMapColour.b;

	color = woodTextureColour + lightfireTextureColour + darkFireTextureColour;
};