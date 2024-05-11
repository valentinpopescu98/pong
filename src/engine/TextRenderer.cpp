#include "TextRenderer.h"
#include "engine/Engine.h"

TextRenderer::TextRenderer(GLuint shaderId, const char* fontPath, int fontSize) {
    this->shaderId = shaderId;

    if (FT_Init_FreeType(&ft)) {
        std::cerr << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return;
    }

    // Load Arial font
    std::string windowsFonts = "C:\\Windows\\Fonts\\";
    if (FT_New_Face(ft, (windowsFonts + fontPath).c_str(), 0, &face)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return;
    }

    FT_Set_Pixel_Sizes(face, 0, fontSize);

    createTextures();
}

TextRenderer::~TextRenderer() {
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void TextRenderer::createTextures() {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    for (unsigned char c = 0; c < 128; c++) {
        // load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }

        // generate texture
        unsigned int textureId;
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows,
            0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // now store character for later use
        Character character = {
            textureId,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        characters.insert(std::pair<char, Character>(c, character));
    }
}

void TextRenderer::renderText(std::string text, glm::vec2 position, glm::vec3 color, float scale) {
    // Create projection matrix by window dimensions
    glm::mat4 proj = glm::ortho(0.0f, static_cast<float>(Engine::resX), 0.0f, static_cast<float>(Engine::resY));
    Utils::sendMatrix4x4Uniform(shaderId, "proj", proj);
    Utils::send3fUniform(shaderId, "textColor", color);

    glActiveTexture(GL_TEXTURE0);

    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) {
        Character ch = characters[*c];

        MeshText* quad = new MeshText(Utils::quadIndices, position, color, ch, scale);
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.textureId);
        quad->render(shaderId);

        // move horizontal to end of character
        position.x += (ch.advance >> 6) * scale;
    }

    glBindTexture(GL_TEXTURE_2D, 0);
}
