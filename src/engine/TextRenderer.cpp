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

    //createTextures(face->glyph->bitmap.buffer, face->glyph->bitmap.width, face->glyph->bitmap.rows);
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
void TextRenderer::renderText(const std::string& text, glm::vec2 pos, glm::vec3 color) {
    if (text == "") {
        return;
    }

    Utils::send1iUniform(shaderId, "useTexture", 1);

    if (text.size() > characters.size()) {
        characters.resize(text.size(), nullptr);
    }

    // horizontal offset for spacing between characters
    float hSpacingOffset = pixelToNormalized(5, Engine::resX);
    for (int i = 0; i < text.size(); i++) {
        unsigned char c = text[i];

        // only ASCII characters are supported
        if (c > 127) {
            return;
        }

        // no reason to draw a blank space
        if (c == ' ') {
            continue;
        }

        // character offset for individual character position in a string
        float hCharOffset = pixelToNormalized(i * fontSize, Engine::resX);

        // try to create texture
        // if freetype fails, do not render
        if (!createTexture(text[i], face->glyph)) {
            continue;
        }

        // width and height of the quad should correspond with the texture
        float width = pixelToNormalized(face->glyph->bitmap.width, Engine::resX);
        float height = pixelToNormalized(face->glyph->bitmap.rows, Engine::resY);

        renderTexture(textures[c], characters[i],
            glm::vec2(pos.x + hCharOffset, pos.y),
            glm::vec2(width, height),
            color
        );
    }

    Utils::send1iUniform(shaderId, "useTexture", 0);
}

bool TextRenderer::createTexture(unsigned char character, FT_GlyphSlot glyph) {
    // if texture not found in cache
    auto it = textures.find(character);
    if (it == textures.end()) {
        // Load character bitmap and create texture
        if (FT_Load_Char(face, character, FT_LOAD_RENDER)) {
            std::cerr << "Failed to load character '" << character << "'" << std::endl;
            return false;
        }

        textures[character] = textures.size() + 1;
        glGenTextures(1, &textures[character]);
    }

    glActiveTexture(GL_TEXTURE0 + (textures[character] - 1) % 32);
    glBindTexture(GL_TEXTURE_2D, textures[character]);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload bitmap data to texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, glyph->bitmap.width, glyph->bitmap.rows,
        0, GL_RED, GL_UNSIGNED_BYTE, glyph->bitmap.buffer);

    Utils::checkForErrors();

    glBindTexture(GL_TEXTURE_2D, 0);

    Utils::send1iUniform(shaderId, "text", (textures[character] - 1) % 32);
}

void TextRenderer::renderTexture(GLuint textureId, Mesh* quad, glm::vec2 pos, glm::vec2 scale, glm::vec3 color) {
    // lazy load meshes if more are needed
    if (quad == NULL) {
        quad = new Mesh(Utils::quadVertices, Utils::quadIndices,
            glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 0), glm::vec3(1, 1, 1), false);
    }
    // for next frames if mesh attributes change, update them into the lazy loaded meshes
    quad->position = glm::vec3(pos.x, pos.y, 0);
    quad->scale = glm::vec3(scale.x, scale.y, 0);
    quad->color = color;

    // Bind texture and render quad for character
    glActiveTexture(GL_TEXTURE0 + (textureId - 1) % 32);
    glBindTexture(GL_TEXTURE_2D, textureId);

    // Render textured quad using shaders and VBOs
    quad->render(shaderId);

    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE0);
}

// pixel in (-1, 1) interval for model matrix
// horizontal offset = interval length * offset in pixels / viewport size
// viewport can be either width or height, depending on which axis the normalization is applied to
float TextRenderer::pixelToNormalized(int pixel, int viewportSize) {
    return 2 * pixel / (float)viewportSize;
}
