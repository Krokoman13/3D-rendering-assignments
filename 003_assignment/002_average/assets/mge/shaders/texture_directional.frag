//DIFFUSE TEXTURE FRAGMENT SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform sampler2D diffuseTexture;
uniform vec3 ambientLightColor;
uniform vec3 directionalLightColor;

in float diffuseIntensity;
in vec2 texCoord;

out vec4 fragment_color;

void main( void ) {
    vec3 diffuseTerm = diffuseIntensity * directionalLightColor;

    fragment_color = vec4(ambientLightColor + diffuseTerm, 1.0f) * texture(diffuseTexture,texCoord);
}
