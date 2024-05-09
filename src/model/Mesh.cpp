#include "Mesh.h"

Mesh::Mesh(std::vector<VertexStruct> vertices, std::vector<GLuint> indices,
    glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 color, bool isCollidable) {
    this->vertices = vertices;
    this->indices = indices;

    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
    this->color = color;

    this->isCollidable = isCollidable;

    // Create buffers
    vao = new VAO(); // Create VAO and bind it
    vbo = new VBO(vertices); // Create VBO, bind and send buffers to GPU
    ebo = new EBO(indices); // Create EBO, bind and send buffers to GPU

    vao->linkVBO(vbo, 0, sizeof(VertexStruct), (void*)0); // Link VBOs to location 0
    vao->linkVBO(vbo, 1, sizeof(VertexStruct), (void*)offsetof(VertexStruct, normals)); // Link VBOs to location 1
    vao->linkVBO(vbo, 2, sizeof(VertexStruct), (void*)offsetof(VertexStruct, textCoords)); // Link VBOs to location 2
    vao->linkVBO(vbo, 3, sizeof(VertexStruct), (void*)offsetof(VertexStruct, colors)); // Link VBOs to location 3

    vao->unbind(); // Unbind VAO
    vbo->unbind(); // Unbind VBO
    ebo->unbind(); // Unbind EBO
}

Mesh::Mesh(std::vector<VertexStruct> vertices, std::vector<GLuint> indices, Mesh& parent,
    glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 color, bool isCollidable)
    : Mesh(vertices, indices, position, rotation, scale, color, isCollidable) {

    this->position += parent.position;
    this->rotation += parent.rotation;
    this->scale *= parent.scale;

    this->isCollidable = isCollidable;
}

Mesh::~Mesh() {
    delete vao; // Unbind VAO
    delete vbo; // Unbind VBO
    delete ebo; // Unbind EBO
}

void Mesh::render(GLuint shaderId) {
    // Create model matrix and calculate object's global position, rotation and scale
    glm::mat4 model = glm::translate(glm::mat4(1.0f), position) *
        glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)) *
        glm::scale(glm::mat4(1.0f), scale);

    // Send view matrix as uniform to the GPU
    Utils::sendMatrix4x4Uniform(shaderId, "model", model);
    // Send color as uniform to the GPU
    Utils::send3fUniform(shaderId, "color", color);

    // Draw mesh
    vao->bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    vao->unbind();
}
