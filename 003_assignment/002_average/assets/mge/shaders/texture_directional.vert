//DIFFUSE TEXTURE VERTEX SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform	mat4 mvpMatrix;
uniform	mat4 modelMatrix;
uniform vec3 directionalLightVector;

in vec3 vertex;
in vec3 normal;
in vec2 uv;

out vec2 texCoord; //make sure the texture coord is interpolated
out float diffuseIntensity;

void main( void ){
    gl_Position = mvpMatrix * vec4(vertex, 1.0f);
	texCoord = uv;

    //make sure normal is in same space as light direction. You should be able to explain the 0.
    vec3 worldNormal = vec3 (modelMatrix * vec4 (normal,0));

    //take the dot of the direction from surface to light with the world surface normal
    diffuseIntensity = max (0, dot(-normalize(directionalLightVector), normalize (worldNormal)));
}
