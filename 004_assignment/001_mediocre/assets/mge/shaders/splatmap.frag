//DIFFUSE TEXTURE FRAGMENT SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform sampler2D textureSplatMap;
uniform sampler2D textureDiffuse1;
uniform sampler2D textureDiffuse2;
uniform sampler2D textureDiffuse3;
uniform sampler2D textureDiffuse4;

in vec2 texCoord;
out vec4 fragment_color;

void main( void ) {
	vec4 splatMapValues = texture(textureSplatMap, texCoord);
	vec4 diffuse1_color = texture(textureDiffuse1, texCoord);
	vec4 diffuse2_color = texture(textureDiffuse2, texCoord);
	vec4 diffuse3_color = texture(textureDiffuse3, texCoord);
	vec4 diffuse4_color = texture(textureDiffuse4, texCoord);

	fragment_color = diffuse1_color * splatMapValues.r + diffuse2_color * splatMapValues.g + diffuse3_color * splatMapValues.b + diffuse4_color * splatMapValues.a;
}
