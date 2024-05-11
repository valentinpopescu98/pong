#version 460 core
layout(location = 0) out vec4 outColor; // Fragment color

in vec3 objPos; // The global position of the object
in vec3 normal; // Input normals from the vertex shader
in vec2 textCoord; // Input texture coordinates from the vertex shader
in vec3 objColor; // Input color from the vertex shader+

uniform int useTexture; // flag that determines whether fragment uses textures or not
uniform sampler2D text; // Value coresponding to the used texture slot

void main() {
	// Sample texture using texture coordinates
	vec4 textColor = texture(text, textCoord);

	// vec3 outNormal = normalize(normal); // Normalize the normals (make it in range [0, 1])

	if (useTexture == 1) {
		outColor =  textColor * vec4(objColor, 1.0f); // Output color of each fragment combined with the texture
	} else {
		outColor =  vec4(objColor, 1.0f); // Output color of each fragment
	}
}