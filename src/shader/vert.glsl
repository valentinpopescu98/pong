#version 460 core
layout(location = 0) in vec3 vPos; // Position of each vertex (XYZ)
layout(location = 1) in vec3 vNormal; // Direction of normal vectors for each vertex (XYZ)
layout(location = 2) in vec3 vColor; // Color of each vertex (RGB)

out vec3 objPos; // The global position of the object
out vec3 objColor; // Output color for the fragment shader
out vec3 normal; // Out normals for the the fragment shader

uniform vec3 color; // The color of all the object
uniform mat4 model; // Model matrix (LOCAL COORDS -> WORLD COORDS)

void main() {
	gl_Position = model * vec4(vPos, 1.0); // 3D position of each vertex
	
	objColor = color; // Send the uniform object color to the fragment shader
	// color = vColor; // Send each vertex color to the fragment shader
	normal = vNormal; // Send normals to the fragment shader

	// Calculate the global position of the object with the use of the model matrix and the local position
	objPos = vec3(model * vec4(vPos, 1.0));
}