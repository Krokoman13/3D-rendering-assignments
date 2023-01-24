#version 330

in vec3 vertex;
in vec3 color;

uniform float scale;
uniform float rotation;
uniform vec2 offset;

out vec2 uv;

vec2 rotateAround(vec2 point, vec2 origin, float angle) {
    float x = ((point.x - origin.x) * cos(angle)) - ((point.y - origin.y) * sin(angle)) + origin.x;
    float y = ((point.x - origin.x) * sin(angle)) + ((point.y - origin.y) * cos(angle)) + origin.y;

    return vec2(x,y);
}

void main (void) {
    gl_Position = vec4(vertex,1) + vec4(offset,0,0);
    uv = vec2(vertex.x, vertex.y) * scale;
    uv = rotateAround(uv, vec2(0,0), rotation);
}