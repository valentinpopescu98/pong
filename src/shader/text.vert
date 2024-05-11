#version 460 core
layout(location = 0) in vec3 vPos; // Position of each vertex (XYZ)
layout(location = 1) in vec2 vTextCoord; // Texture coordinates of each vertex (UV)

out vec2 textCoord; // Output texture coordinates for the fragment shader

uniform mat4 proj;

void main() {
    gl_Position = proj * vec4(vPos, 1.0); // 3D position of each vertex
    textCoord = vTextCoord; // Send texture coordinates to the fragment shader
}