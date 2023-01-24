//DIFFUSE TEXTURE VERTEX SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform	mat4 mvpMatrix;
uniform mat4 modelMatrix;
//uniform mat4 modelvieuwMatrix;

in vec3 vertex;
in vec3 normal;
in vec2 uv;

out vec3 intpPosition;       // This will be passed into the fragment shader.
out vec3 intpNormal;         // This will be passed into the fragment shader.
out vec2 texCoord;           // make sure the texture coord is interpolated

void main( void )
{
    gl_Position = mvpMatrix * vec4(vertex, 1.0f);
	texCoord = uv;

    // Transform the vertex into world space.
    intpPosition = vec3(modelMatrix * vec4(vertex, 1.0));
 
    // Transform the normal's orientation into world space.
    intpNormal = mat3(transpose(inverse(modelMatrix))) * normal;
}