//DIFFUSE TEXTURE FRAGMENT SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform sampler2D diffuseTexture;
uniform vec3 intpLightPos;
uniform vec3 ambientLightColor;
uniform vec3 pointLightColor;
uniform float lightIntensity = 100.0f;   //Signifies the strength of the light
uniform float shininess = 32;  //Signifies the shininess of the material
uniform vec3 specularColor = vec3(1,1,1); //Signifies the specularColor of the material
uniform vec3 cameraPos;

in vec3 intpPosition;
in vec3 intpNormal;
in vec2 texCoord;


void main( void )
{
    vec3 diffrence = intpLightPos - intpPosition;

    // Will be used for attenuation.
    float dist = length(diffrence);
 
    // Get a lighting direction vector from the light to the vertex.
    vec3 lightVector = normalize(diffrence);

    //Get a normalized version of the normal
    vec3 norm = normalize(intpNormal);
 
    // Calculate the dot product of the light vector and vertex normal. If the normal and light vector are
    // pointing in the same direction then it will get max illumination.
    float diffuse = max(dot(lightVector, norm), 0.0);

    vec3 diffuseTerm = pointLightColor * diffuse;


    // Calculate attenuation.
    float attenuation = 1.0 / (1.0 + 0.1 * dist + 0.001 * dist * dist);

    vec3 reflectDir = reflect(-lightVector, norm);
    vec3 viewDir = normalize(cameraPos - intpPosition);

    vec3 specularTerm = pow(max(dot(viewDir, reflectDir), 0.0f), 32) * pointLightColor * 3.0;  

    // Multiply the color by the diffuse illumination level to get final output color.
    gl_FragColor = vec4(ambientLightColor + specularTerm * attenuation + diffuseTerm * attenuation, 1.0f) * texture(diffuseTexture, texCoord);
}