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

    createTextures(face->glyph->bitmap.buffer, face->glyph->bitmap.width, face->glyph->bitmap.rows);
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
    if (text == "") {
        return;
    }

    Utils::send1iUniform(shaderId, "useTexture", 1);

    characters.resize(text.size(), nullptr);

    // horizontal offset
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

        Utils::send1iUniform(shaderId, "text", textures[c]);

        // Calculate position and size of quad
        float charOffset = pixelToNormalized(i * fontSize, Engine::resX);
        // lazy load meshes if more are needed
        if (characters[i] == NULL) {
            characters[i] = new Mesh(Utils::quadVertices, Utils::quadIndices,
                glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 0), glm::vec3(1, 1, 1), false);
        }
        // for next frames if mesh attributes change, update them into the lazy loaded meshes
        characters[i]->position = glm::vec3(pos.x + charOffset + (i == 0 ? 0 : hSpacingOffset), pos.y, 0);
        characters[i]->scale = glm::vec3(scale.x, scale.y, 0);
        characters[i]->color = color;

        // Bind texture and render quad for character
        glBindTexture(GL_TEXTURE_2D, textures[c]);

        // Render textured quad using shaders and VBOs
        characters[i]->render(shaderId);

        glBindTexture(GL_TEXTURE_2D, 0);
        glActiveTexture(GL_TEXTURE0);
    }

    Utils::send1iUniform(shaderId, "useTexture", 0);
}

void TextRenderer::createTextures(const unsigned char* buffer, int width, int height) {
    // Generate OpenGL texture for each character
    for (unsigned char c = 0; c < 128; c++) {
        // Load character bitmap and create texture
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            continue;
        }

        glGenTextures(1, &textures[c]);
        glActiveTexture(GL_TEXTURE0 + c);
        glBindTexture(GL_TEXTURE_2D, textures[c]);

        // Set texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Upload bitmap data to texture
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, buffer);

        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

// pixel position in normalized in (-1, 1) interval for model matrix
// horizontal offset = interval length * offset in pixels / viewport size
// viewport can be either width or height, depending on which axis the normalization is applied to
float TextRenderer::pixelToNormalized(float pixelPos, float viewportSize) {
    return 2 * pixelPos / viewportSize;
}
