#version 460 core

layout(location = 0) out vec4 outColor; // Fragment color

in vec3 objPos; // The global position of the object
in vec3 objColor; // Input color from the vertex shader
in vec3 normal; // Input normals from the vertex shader

void main() {
	// vec3 outNormal = normalize(normal); // Normalize the normals (make it in range [0, 1])

	outColor =  vec4(objColor, 1.0f); // Output color of each fragment
}