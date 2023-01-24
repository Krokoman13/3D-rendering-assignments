//DIFFUSE TEXTURE VERTEX SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform	mat4 mvpMatrix;

in vec3 vertex;
in vec3 normal;
in vec2 uv;

out vec2 texCoord; //make sure the texture coord is interpolated

uniform sampler2D heightMapTexture;
uniform float scale = 10.0;
uniform float offset = 0.0;

void main( void ) {
	texCoord = uv;

	vec4 hightmapValue = texture2D(heightMapTexture, texCoord);
	float normalizedHeight = ((hightmapValue.r + hightmapValue.g + hightmapValue.b + hightmapValue.a)/4);
	float height = offset + scale * normalizedHeight;

	vec4 pos = mvpMatrix * vec4(vertex, 1.f);
	pos.y += height;
	gl_Position = pos;
}    