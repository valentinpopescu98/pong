#version 460 core
out vec4 color; // Fragment color

in vec2 textCoord; // Input texture coordinates from the vertex shader

uniform sampler2D text; // Value coresponding to the used texture slot
uniform vec3 textColor; // Color mixed with texture's color

void main() {    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, textCoord).r);
    color = vec4(textColor, 1.0) * sampled;
}