#version 460 core
layout(location = 0) in vec3 vPos; // Position of each vertex (XYZ)
layout(location = 1) in vec3 vNormal; // Direction of normal vectors for each vertex (XYZ)
layout(location = 2) in vec2 vTextCoord; // Texture coordinates of each vertex (UV)
layout(location = 3) in vec3 vColor; // Color of each vertex (RGB)

out vec3 objPos; // The global position of the object
out vec3 normal; // Out normals for the the fragment shader
out vec2 textCoord; // Output texture coordinates for the fragment shader
out vec3 objColor; // Output color for the fragment shader

uniform vec3 color; // The color of all the object
uniform mat4 model; // Model matrix (LOCAL COORDS -> WORLD COORDS)

void main() {
	gl_Position = model * vec4(vPos, 1.0); // 3D position of each vertex
	
	if (color == vec3(0.0)) {
		objColor = vColor; // Send each vertex color to the fragment shader
	} else {
		objColor = color; // Send the uniform object color to the fragment shader
	}
	textCoord = vTextCoord; // Send texture coordinates to the fragment shader
	normal = vNormal; // Send normals to the fragment shader

	// Calculate the global position of the object with the use of the model matrix and the local position
	objPos = vec3(model * vec4(vPos, 1.0));
}