#include "MeshText.h"

MeshText::MeshText(std::vector<GLuint> indices, glm::vec2 position, glm::vec3 color, Character ch, float scale) {
    this->indices = indices;

    this->position = position;
    this->color = color;
    this->scale = scale;

    // position after spacing
    glm::vec2 newPos = glm::vec2(
        position.x + ch.bearing.x * scale, // first pixel behind the glyph
        position.y - (ch.size.y - ch.bearing.y) * scale // first pixel under the glyph
    );
    // scale on x and y axis
    glm::vec2 newScale = glm::vec2(
        ch.size.x * scale,
        ch.size.y * scale
    );

    this->vertices = {
        //	        COORDS                                          TEXT COORDS
        {glm::vec3(newPos.x,              newPos.y + newScale.y, 0), glm::vec2(0, 0)}, // bottom left
        {glm::vec3(newPos.x,              newPos.y,              0), glm::vec2(0, 1)}, // top left
        {glm::vec3(newPos.x + newScale.x, newPos.y,              0), glm::vec2(1, 1)}, // top right
        {glm::vec3(newPos.x + newScale.x, newPos.y + newScale.y, 0), glm::vec2(1, 0)}  // bottom right
    };

    // Create buffers
    vao = new VAO_Text(); // Create VAO and bind it
    vbo = new VBO_Text(vertices); // Create VBO, bind and send buffers to GPU
    ebo = new EBO(indices); // Create EBO, bind and send buffers to GPU

    vao->linkVBO(vbo, 0, sizeof(TextVertexStruct), (void*)0); // Link VBOs to location 0
    vao->linkVBO(vbo, 1, sizeof(TextVertexStruct), (void*)offsetof(TextVertexStruct, textCoords)); // Link VBOs to location 1

    vao->unbind(); // Unbind VAO
    vbo->unbind(); // Unbind VBO
    ebo->unbind(); // Unbind EBO
}

MeshText::~MeshText() {
    delete vao; // Unbind VAO
    delete vbo; // Unbind VBO
    delete ebo; // Unbind EBO
}

void MeshText::render(GLuint shaderId) {
    // Draw mesh
    vao->bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    vao->unbind();
}
