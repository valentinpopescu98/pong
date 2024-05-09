#include "TextRenderer.h"
#include "engine/Engine.h"

TextRenderer::TextRenderer(GLuint shaderId, const char* fontPath, int fontSize) {
    this->shaderId = shaderId;
    this->fontSize = fontSize;

    if (FT_Init_FreeType(&ft)) {
        // Handle error
        return;
    }

    // Load Arial font
    std::string windowsFonts = "C:\\Windows\\Fonts\\";
    if (FT_New_Face(ft, (windowsFonts + fontPath).c_str(), 0, &face)) {
        // Handle error
        return;
    }

    FT_Set_Pixel_Sizes(face, 0, fontSize);

    // Generate OpenGL texture for each character
    for (unsigned char c = 0; c < 128; c++) {
        // Load character bitmap and create texture
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            continue;
        }

        createTexture(face->glyph->bitmap.buffer, face->glyph->bitmap.width, face->glyph->bitmap.rows, c);
    }
}

TextRenderer::~TextRenderer() {
    for (auto& pair : textures) {
        // Delete texture
        glDeleteTextures(1, &(pair.second));
    }
    // Clear the map
    textures.clear();

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

// Function to render text using FreeType and OpenGL
void TextRenderer::renderText(const std::string& text, glm::vec2 pos, glm::vec2 scale, glm::vec3 color) {
    Utils::send1iUniform(shaderId, "useTexture", 1);

    std::vector<Mesh*> characters;
    characters.resize(text.size(), nullptr);

    // horizontal offset
    float hSpacingOffset = pixelToNormalized(5, Engine::windowWidth);
    for (int i = 0; i < text.size(); i++) {
        char c = text[i];

        // only ASCII characters are supported
        if (static_cast<unsigned char>(c) > 127) {
            return;
        }

        // no reason to draw a blank space
        if (c == ' ') {
            continue;
        }

        // Calculate position and size of quad
        float charOffset = pixelToNormalized(i * fontSize, Engine::windowWidth);
        characters[i] = new Mesh(Utils::quadVertices, Utils::quadIndices,
            glm::vec3(pos.x + charOffset + hSpacingOffset, pos.y, 0),
            glm::vec3(0, 0, 0), glm::vec3(scale.x, scale.y, 0), color, false);

        // Bind texture and render quad for character
        GLuint texture = textures[c];
        glBindTexture(GL_TEXTURE_2D, texture);

        // Render textured quad using shaders and VBOs
        characters[i]->render(shaderId);

        glBindTexture(GL_TEXTURE_2D, 0);
        glActiveTexture(GL_TEXTURE0);
    }

    Utils::send1iUniform(shaderId, "useTexture", 0);
}

void TextRenderer::createTexture(const unsigned char* buffer, int width, int height, GLchar character) {
    GLuint texture = character;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0 + character);

    Utils::send1iUniform(shaderId, "text", 1);

    glBindTexture(GL_TEXTURE_2D, texture);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload bitmap data to texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, buffer);

    // Add texture to characterTextures map
    textures[character] = texture;

    glBindTexture(GL_TEXTURE_2D, 0);
}

// pixel position in normalized in (-1, 1) interval for model matrix
// horizontal offset = interval length * offset in pixels / viewport size
// viewport can be either width or height, depending on which axis the normalization is applied to
float TextRenderer::pixelToNormalized(float pixelPos, float viewportSize) {
    return 2 * pixelPos / viewportSize;
}

void TextRenderer::setShaderId(GLuint shaderId) {
    this->shaderId = shaderId;
}
